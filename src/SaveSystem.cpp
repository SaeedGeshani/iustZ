#include "SaveSystem.h"

#include <filesystem>
#include <fstream>
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

    out = it->second.get<int>();
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
