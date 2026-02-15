#include "SaveSystem.h"

#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>

#include <nlohmann/json.hpp>

namespace
{
std::string EscapeJson(const std::string& value)
{
    std::string out;
    out.reserve(value.size());
    for (char c : value)
    {
        switch (c)
        {
        case '\\': out += "\\\\"; break;
        case '"': out += "\\\""; break;
        case '\n': out += "\\n"; break;
        case '\r': out += "\\r"; break;
        case '\t': out += "\\t"; break;
        default: out += c; break;
        }
    }
    return out;
}

std::string Quote(const std::string& value)
{
    return "\"" + EscapeJson(value) + "\"";
}

std::string SerializeStringArray(const std::vector<std::string>& values)
{
    std::ostringstream out;
    out << "[";
    for (std::size_t i = 0; i < values.size(); ++i)
    {
        out << Quote(values[i]);
        if (i + 1 < values.size())
        {
            out << ",";
        }
    }
    out << "]";
    return out.str();
}

std::filesystem::path BuildSavePath(const std::string& slotName)
{
    return std::filesystem::path("saves") / (slotName + ".json");
}

bool ReadRequiredInt(const nlohmann::json& object, const char* key, int& out)
{
    const nlohmann::json::const_iterator it = object.find(key);
    if (it == object.end() || !it->second.is_number_integer())
    {
        return false;
    }

    const long long raw = it->second.get<long long>();
    if (raw < static_cast<long long>(std::numeric_limits<int>::min())
        || raw > static_cast<long long>(std::numeric_limits<int>::max()))
    {
        return false;
    }

    out = static_cast<int>(raw);
    return true;
}

bool ReadRequiredString(const nlohmann::json& object, const char* key, std::string& out)
{
    const nlohmann::json::const_iterator it = object.find(key);
    if (it == object.end() || !it->second.is_string())
    {
        return false;
    }

    out = it->second.get<std::string>();
    return true;
}

bool ReadStringArray(const nlohmann::json& object, const char* key, std::vector<std::string>& out)
{
    const nlohmann::json::const_iterator it = object.find(key);
    if (it == object.end() || !it->second.is_array())
    {
        return false;
    }

    const nlohmann::json::array_t* arr = it->second.as_array();
    if (!arr)
    {
        return false;
    }

    out.clear();
    for (const nlohmann::json& entry : *arr)
    {
        if (!entry.is_string())
        {
            return false;
        }
        out.push_back(entry.get<std::string>());
    }

    return true;
}

bool ReadOptionalInt(const nlohmann::json& object, const char* key, int defaultValue, int& out)
{
    const nlohmann::json::const_iterator it = object.find(key);
    if (it == object.end())
    {
        out = defaultValue;
        return true;
    }

    return ReadRequiredInt(object, key, out);
}

bool ParsePlayerNode(const nlohmann::json& playerNode, const nlohmann::json& inventoryNode, const nlohmann::json& equippedWeaponNode, GameState& loaded)
{
    if (!ReadRequiredString(playerNode, "name", loaded.playerName)
        || !ReadRequiredString(playerNode, "gender", loaded.gender)
        || !ReadRequiredInt(playerNode, "hp", loaded.hp)
        || !ReadRequiredInt(playerNode, "xp", loaded.xp)
        || !ReadRequiredInt(playerNode, "lvl", loaded.lvl)
        || !ReadRequiredInt(playerNode, "coins", loaded.coins)
        || !ReadRequiredInt(playerNode, "dm", loaded.dm)
        || !ReadRequiredInt(playerNode, "stamina", loaded.stamina)
        || !ReadRequiredInt(playerNode, "kills", loaded.kills))
    {
        return false;
    }

    if (!ReadStringArray(inventoryNode, "weapons", loaded.weaponsOwnedNames)
        || !ReadStringArray(inventoryNode, "items", loaded.usableItemsOwnedNames))
    {
        return false;
    }

    if (!equippedWeaponNode.is_string())
    {
        return false;
    }

    loaded.equippedWeapon = equippedWeaponNode.get<std::string>();
    return true;
}
} // namespace

bool SaveGame(const GameState& state, const std::string& slotName, std::string* err)
{
    std::error_code ec;
    std::filesystem::create_directories("saves", ec);
    if (ec)
    {
        if (err)
        {
            *err = "Could not create saves directory: " + ec.message();
        }
        return false;
    }

    const auto savePath = BuildSavePath(slotName);
    std::ofstream output(savePath, std::ios::trunc);
    if (!output.is_open())
    {
        if (err)
        {
            *err = "Could not open save file for writing: " + savePath.string();
        }
        return false;
    }

    output
        << "{\n"
        << "  \"version\": 1,\n"
        << "  \"player\": { \"name\": " << Quote(state.playerName)
        << ", \"gender\": " << Quote(state.gender)
        << ", \"hp\": " << state.hp
        << ", \"xp\": " << state.xp
        << ", \"lvl\": " << state.lvl
        << ", \"coins\": " << state.coins
        << ", \"dm\": " << state.dm
        << ", \"stamina\": " << state.stamina
        << ", \"kills\": " << state.kills << " },\n"
        << "  \"inventory\": {\n"
        << "    \"weapons\": " << SerializeStringArray(state.weaponsOwnedNames) << ",\n"
        << "    \"items\": " << SerializeStringArray(state.usableItemsOwnedNames) << "\n"
        << "  },\n"
        << "  \"equippedWeapon\": " << Quote(state.equippedWeapon) << "\n"
        << "}\n";

    if (!output.good())
    {
        if (err)
        {
            *err = "Failed to write complete save file: " + savePath.string();
        }
        return false;
    }

    return true;
}

bool LoadGame(GameState& outState, const std::string& slotName, std::string* err)
{
    const auto savePath = BuildSavePath(slotName);
    std::error_code ec;
    if (!std::filesystem::exists(savePath, ec) || ec)
    {
        if (err)
        {
            *err = "Save not found: " + savePath.string();
        }
        return false;
    }

    std::ifstream input(savePath);
    if (!input.is_open())
    {
        if (err)
        {
            *err = "Corrupt save: could not open " + savePath.string();
        }
        return false;
    }

    nlohmann::json parsed;
    try
    {
        input >> parsed;
    }
    catch (const nlohmann::json::parse_error&)
    {
        if (err)
        {
            *err = "Corrupt save: invalid JSON in " + savePath.string();
        }
        return false;
    }

    if (!parsed.is_object())
    {
        if (err)
        {
            *err = "Corrupt save: root object missing in " + savePath.string();
        }
        return false;
    }

    int version = 0;
    if (!ReadRequiredInt(parsed, "version", version))
    {
        if (err)
        {
            *err = "Corrupt save: missing version in " + savePath.string();
        }
        return false;
    }

    if (version != 1)
    {
        if (err)
        {
            *err = "Old version save is not supported: " + savePath.string();
        }
        return false;
    }

    const nlohmann::json::const_iterator playerIt = parsed.find("player");
    if (playerIt == parsed.end() || !playerIt->second.is_object())
    {
        if (err)
        {
            *err = "Corrupt save: missing player object in " + savePath.string();
        }
        return false;
    }

    const nlohmann::json::const_iterator inventoryIt = parsed.find("inventory");
    if (inventoryIt == parsed.end() || !inventoryIt->second.is_object())
    {
        if (err)
        {
            *err = "Corrupt save: missing inventory object in " + savePath.string();
        }
        return false;
    }

    GameState loaded;
    if (!ReadRequiredString(playerIt->second, "name", loaded.playerName)
        || !ReadRequiredString(playerIt->second, "gender", loaded.gender)
        || !ReadRequiredInt(playerIt->second, "hp", loaded.hp)
        || !ReadRequiredInt(playerIt->second, "xp", loaded.xp)
        || !ReadRequiredInt(playerIt->second, "lvl", loaded.lvl)
        || !ReadRequiredInt(playerIt->second, "coins", loaded.coins)
        || !ReadRequiredInt(playerIt->second, "dm", loaded.dm)
        || !ReadRequiredInt(playerIt->second, "stamina", loaded.stamina)
        || !ReadRequiredInt(playerIt->second, "kills", loaded.kills))
    {
        if (err)
        {
            *err = "Corrupt save: missing required player fields in " + savePath.string();
        }
        return false;
    }

    if (!ReadStringArray(inventoryIt->second, "weapons", loaded.weaponsOwnedNames)
        || !ReadStringArray(inventoryIt->second, "items", loaded.usableItemsOwnedNames))
    {
        if (err)
        {
            *err = "Corrupt save: invalid inventory arrays in " + savePath.string();
        }
        return false;
    }

    if (!ReadRequiredString(parsed, "equippedWeapon", loaded.equippedWeapon))
    {
        if (err)
        {
            *err = "Corrupt save: missing equipped weapon in " + savePath.string();
        }
        return false;
    }

    outState = loaded;
    return true;
}

bool SaveSession(const SessionState& state, const std::string& slotName, std::string* err)
{
    std::error_code ec;
    std::filesystem::create_directories("saves", ec);
    if (ec)
    {
        if (err)
        {
            *err = "Could not create saves directory: " + ec.message();
        }
        return false;
    }

    const auto savePath = BuildSavePath(slotName);
    std::ofstream output(savePath, std::ios::trunc);
    if (!output.is_open())
    {
        if (err)
        {
            *err = "Could not open save file for writing: " + savePath.string();
        }
        return false;
    }

    output << "{\n";
    output << "  \"version\": 2,\n";
    output << "  \"mode\": " << Quote(state.mode) << ",\n";
    output << "  \"partySize\": " << state.party.size() << ",\n";
    output << "  \"party\": [\n";

    for (std::size_t i = 0; i < state.party.size(); ++i)
    {
        const GameState& player = state.party[i];
        output << "    {\n";
        output << "      \"name\": " << Quote(player.playerName) << ",\n";
        output << "      \"gender\": " << Quote(player.gender) << ",\n";
        output << "      \"hp\": " << player.hp << ",\n";
        output << "      \"xp\": " << player.xp << ",\n";
        output << "      \"lvl\": " << player.lvl << ",\n";
        output << "      \"coins\": " << player.coins << ",\n";
        output << "      \"dm\": " << player.dm << ",\n";
        output << "      \"stamina\": " << player.stamina << ",\n";
        output << "      \"kills\": " << player.kills << ",\n";
        output << "      \"equippedWeapon\": " << Quote(player.equippedWeapon) << ",\n";
        output << "      \"inventory\": {\n";
        output << "        \"weapons\": " << SerializeStringArray(player.weaponsOwnedNames) << ",\n";
        output << "        \"items\": " << SerializeStringArray(player.usableItemsOwnedNames) << "\n";
        output << "      }\n";
        output << "    }";
        if (i + 1 < state.party.size())
        {
            output << ",";
        }
        output << "\n";
    }

    output << "  ],\n";
    output << "  \"session\": {\n";
    output << "    \"sharedCoins\": " << (state.sharedCoins ? 1 : 0) << ",\n";
    output << "    \"difficulty\": " << state.difficulty << ",\n";
    output << "    \"battleIndex\": " << state.battleIndex << "\n";
    output << "  }\n";
    output << "}\n";

    if (!output.good())
    {
        if (err)
        {
            *err = "Failed to write complete save file: " + savePath.string();
        }
        return false;
    }

    return true;
}

bool LoadSession(SessionState& outState, const std::string& slotName, std::string* err)
{
    const auto savePath = BuildSavePath(slotName);
    std::ifstream input(savePath);
    if (!input.is_open())
    {
        if (err)
        {
            *err = "Save not found or unreadable: " + savePath.string();
        }
        return false;
    }

    nlohmann::json parsed;
    try
    {
        input >> parsed;
    }
    catch (const nlohmann::json::parse_error&)
    {
        if (err)
        {
            *err = "Corrupt save: invalid JSON in " + savePath.string();
        }
        return false;
    }

    int version = 0;
    if (!ReadRequiredInt(parsed, "version", version) || version != 2)
    {
        if (err)
        {
            *err = "Legacy save format detected (expected version 2 session): " + savePath.string();
        }
        return false;
    }

    std::string mode;
    if (!ReadRequiredString(parsed, "mode", mode))
    {
        if (err)
        {
            *err = "Corrupt save: missing mode in " + savePath.string();
        }
        return false;
    }

    const nlohmann::json::const_iterator partyIt = parsed.find("party");
    if (partyIt == parsed.end() || !partyIt->second.is_array())
    {
        if (err)
        {
            *err = "Corrupt save: missing party array in " + savePath.string();
        }
        return false;
    }

    SessionState loaded;
    loaded.version = 2;
    loaded.mode = mode;

    int declaredPartySize = 0;
    if (!ReadRequiredInt(parsed, "partySize", declaredPartySize) || declaredPartySize < 1)
    {
        if (err)
        {
            *err = "Corrupt save: invalid party size in " + savePath.string();
        }
        return false;
    }

    const nlohmann::json::array_t* partyArray = partyIt->second.as_array();
    if (!partyArray)
    {
        if (err)
        {
            *err = "Corrupt save: invalid party array in " + savePath.string();
        }
        return false;
    }

    for (const nlohmann::json& entry : *partyArray)
    {
        if (!entry.is_object())
        {
            if (err)
            {
                *err = "Corrupt save: invalid party member entry in " + savePath.string();
            }
            return false;
        }

        const nlohmann::json::const_iterator inventoryIt = entry.find("inventory");
        const nlohmann::json::const_iterator equippedWeaponIt = entry.find("equippedWeapon");
        if (inventoryIt == entry.end() || !inventoryIt->second.is_object() || equippedWeaponIt == entry.end())
        {
            if (err)
            {
                *err = "Corrupt save: invalid party member inventory in " + savePath.string();
            }
            return false;
        }

        GameState player;
        if (!ParsePlayerNode(entry, inventoryIt->second, equippedWeaponIt->second, player))
        {
            if (err)
            {
                *err = "Corrupt save: missing required player fields in " + savePath.string();
            }
            return false;
        }

        loaded.party.push_back(player);
    }

    loaded.partySize = static_cast<int>(loaded.party.size());
    if (loaded.partySize != declaredPartySize)
    {
        if (err)
        {
            *err = "Corrupt save: party size mismatch in " + savePath.string();
        }
        return false;
    }

    const nlohmann::json::const_iterator sessionIt = parsed.find("session");
    if (sessionIt != parsed.end())
    {
        int sharedCoinsInt = 0;
        if (!sessionIt->second.is_object()
            || !ReadOptionalInt(sessionIt->second, "sharedCoins", 0, sharedCoinsInt)
            || !ReadOptionalInt(sessionIt->second, "difficulty", 1, loaded.difficulty)
            || !ReadOptionalInt(sessionIt->second, "battleIndex", 0, loaded.battleIndex))
        {
            if (err)
            {
                *err = "Corrupt save: invalid session fields in " + savePath.string();
            }
            return false;
        }
        loaded.sharedCoins = (sharedCoinsInt != 0);
    }

    outState = loaded;
    return true;
}

bool LoadSessionPreview(SessionSlotPreview& outPreview, const std::string& slotName, std::string* err)
{
    const auto savePath = BuildSavePath(slotName);
    std::ifstream input(savePath);
    if (!input.is_open())
    {
        if (err)
        {
            *err = "Could not open save file: " + savePath.string();
        }
        return false;
    }

    nlohmann::json parsed;
    try
    {
        input >> parsed;
    }
    catch (const nlohmann::json::parse_error&)
    {
        if (err)
        {
            *err = "Invalid JSON in save: " + savePath.string();
        }
        return false;
    }

    SessionSlotPreview preview;
    preview.slotName = slotName;

    int version = 0;
    if (!ReadRequiredInt(parsed, "version", version))
    {
        if (err)
        {
            *err = "Missing version in save: " + savePath.string();
        }
        return false;
    }

    if (version == 1)
    {
        preview.isLegacySinglePlayer = true;
        outPreview = preview;
        return true;
    }

    if (version == 2)
    {
        preview.isSessionV2 = true;
        const nlohmann::json::const_iterator partyIt = parsed.find("party");
        if (partyIt != parsed.end() && partyIt->second.is_array())
        {
            const nlohmann::json::array_t* partyArray = partyIt->second.as_array();
            if (partyArray)
            {
                for (const nlohmann::json& partyMember : *partyArray)
                {
                    std::string playerName;
                    if (partyMember.is_object() && ReadRequiredString(partyMember, "name", playerName))
                    {
                        preview.partyNames.push_back(playerName);
                    }
                }
            }
        }
    }

    outPreview = preview;
    return true;
}
