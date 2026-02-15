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

std::filesystem::path BuildSavePath(const std::string& slotId)
{
    return std::filesystem::path("saves") / (slotId + ".json");
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

bool ParsePartyArray(const nlohmann::json& parsed, std::vector<GameState>& outParty)
{
    const nlohmann::json::const_iterator partyIt = parsed.find("party");
    if (partyIt == parsed.end() || !partyIt->second.is_array())
    {
        return false;
    }

    const nlohmann::json::array_t* partyArray = partyIt->second.as_array();
    if (!partyArray)
    {
        return false;
    }

    outParty.clear();
    for (const nlohmann::json& entry : *partyArray)
    {
        if (!entry.is_object())
        {
            return false;
        }

        const nlohmann::json::const_iterator inventoryIt = entry.find("inventory");
        const nlohmann::json::const_iterator equippedWeaponIt = entry.find("equippedWeapon");
        if (inventoryIt == entry.end() || !inventoryIt->second.is_object() || equippedWeaponIt == entry.end())
        {
            return false;
        }

        GameState player;
        if (!ParsePlayerNode(entry, inventoryIt->second, equippedWeaponIt->second, player))
        {
            return false;
        }

        outParty.push_back(player);
    }

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

    const nlohmann::json::const_iterator playerIt = parsed.find("player");
    const nlohmann::json::const_iterator inventoryIt = parsed.find("inventory");
    if (playerIt == parsed.end() || !playerIt->second.is_object() || inventoryIt == parsed.end() || !inventoryIt->second.is_object())
    {
        if (err)
        {
            *err = "Corrupt save: missing player/inventory in " + savePath.string();
        }
        return false;
    }

    GameState loaded;
    const nlohmann::json::const_iterator equippedWeaponIt = parsed.find("equippedWeapon");
    if (equippedWeaponIt == parsed.end()
        || !ParsePlayerNode(playerIt->second, inventoryIt->second, equippedWeaponIt->second, loaded))
    {
        if (err)
        {
            *err = "Corrupt save: missing required player fields in " + savePath.string();
        }
        return false;
    }

    outState = loaded;
    return true;
}

bool SaveSession(const SessionState& state, const std::string& slotId, std::string* err)
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

    const auto savePath = BuildSavePath(slotId);
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
    output << "  \"version\": 3,\n";
    output << "  \"slotId\": " << Quote(state.slotId.empty() ? slotId : state.slotId) << ",\n";
    output << "  \"slotLabel\": " << Quote(state.slotLabel) << ",\n";
    output << "  \"createdAt\": " << Quote(state.createdAt) << ",\n";
    output << "  \"updatedAt\": " << Quote(state.updatedAt) << ",\n";
    output << "  \"mode\": " << Quote(state.mode) << ",\n";
    output << "  \"partyPreview\": [";
    for (std::size_t i = 0; i < state.party.size(); ++i)
    {
        output << Quote(state.party[i].playerName);
        if (i + 1 < state.party.size())
        {
            output << ",";
        }
    }
    output << "],\n";
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

bool LoadSession(SessionState& outState, const std::string& slotId, std::string* err)
{
    const auto savePath = BuildSavePath(slotId);
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
    if (!ReadRequiredInt(parsed, "version", version))
    {
        if (err)
        {
            *err = "Corrupt save: missing version " + savePath.string();
        }
        return false;
    }

    SessionState loaded;
    if (version == 3)
    {
        loaded.version = 3;
        if (!ReadRequiredString(parsed, "slotId", loaded.slotId)
            || !ReadRequiredString(parsed, "slotLabel", loaded.slotLabel)
            || !ReadRequiredString(parsed, "createdAt", loaded.createdAt)
            || !ReadRequiredString(parsed, "updatedAt", loaded.updatedAt)
            || !ReadRequiredString(parsed, "mode", loaded.mode))
        {
            if (err)
            {
                *err = "Corrupt save: missing metadata fields in " + savePath.string();
            }
            return false;
        }
    }
    else if (version == 2)
    {
        loaded.version = 2;
        loaded.slotId = slotId;
        loaded.slotLabel = slotId + " (legacy)";
        loaded.createdAt = "";
        loaded.updatedAt = "";
        if (!ReadRequiredString(parsed, "mode", loaded.mode))
        {
            if (err)
            {
                *err = "Corrupt save: missing mode in " + savePath.string();
            }
            return false;
        }
    }
    else
    {
        if (err)
        {
            *err = "Legacy save format detected (expected version 3 session): " + savePath.string();
        }
        return false;
    }

    if (!ParsePartyArray(parsed, loaded.party))
    {
        if (err)
        {
            *err = "Corrupt save: invalid party array in " + savePath.string();
        }
        return false;
    }

    int declaredPartySize = 0;
    if (!ReadRequiredInt(parsed, "partySize", declaredPartySize) || declaredPartySize < 1)
    {
        if (err)
        {
            *err = "Corrupt save: invalid party size in " + savePath.string();
        }
        return false;
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

bool LoadSessionPreview(SessionSlotPreview& outPreview, const std::string& slotId, std::string* err)
{
    const auto savePath = BuildSavePath(slotId);

    SessionSlotPreview preview;
    preview.slotId = slotId;
    preview.slotLabel = slotId;

    std::ifstream input(savePath);
    if (!input.is_open())
    {
        preview.isCorrupt = true;
        outPreview = preview;
        if (err)
        {
            *err = "Could not open save file: " + savePath.string();
        }
        return true;
    }

    nlohmann::json parsed;
    try
    {
        input >> parsed;
    }
    catch (const nlohmann::json::parse_error&)
    {
        preview.isCorrupt = true;
        outPreview = preview;
        if (err)
        {
            *err = "Invalid JSON in save: " + savePath.string();
        }
        return true;
    }

    int version = 0;
    if (!ReadRequiredInt(parsed, "version", version))
    {
        preview.isCorrupt = true;
        outPreview = preview;
        if (err)
        {
            *err = "Missing version in save: " + savePath.string();
        }
        return true;
    }

    if (version != 3)
    {
        preview.isLegacy = true;
        preview.slotLabel = slotId + " (legacy)";

        if (version == 2)
        {
            ReadRequiredString(parsed, "mode", preview.mode);
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
                            preview.partyPreview.push_back(playerName);
                        }
                    }
                }
            }
        }
        else if (version == 1)
        {
            preview.mode = "singleplayer";
            const nlohmann::json::const_iterator playerIt = parsed.find("player");
            if (playerIt != parsed.end() && playerIt->second.is_object())
            {
                std::string playerName;
                if (ReadRequiredString(playerIt->second, "name", playerName))
                {
                    preview.partyPreview.push_back(playerName);
                }
            }
        }

        outPreview = preview;
        return true;
    }

    preview.isCurrentSlot = true;
    if (!ReadRequiredString(parsed, "slotId", preview.slotId)
        || !ReadRequiredString(parsed, "slotLabel", preview.slotLabel)
        || !ReadRequiredString(parsed, "createdAt", preview.createdAt)
        || !ReadRequiredString(parsed, "updatedAt", preview.updatedAt)
        || !ReadRequiredString(parsed, "mode", preview.mode)
        || !ReadStringArray(parsed, "partyPreview", preview.partyPreview))
    {
        preview.isCorrupt = true;
        preview.isCurrentSlot = false;
    }

    outPreview = preview;
    return true;
}
