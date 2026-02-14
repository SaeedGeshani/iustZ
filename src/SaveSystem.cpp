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

bool ExtractStringValue(const std::string& text, const std::string& key, std::string& out)
{
    const std::string token = "\"" + key + "\"";
    const std::size_t keyPos = text.find(token);
    if (keyPos == std::string::npos)
    {
        return false;
    }

    const std::size_t colonPos = text.find(':', keyPos + token.size());
    const std::size_t firstQuote = text.find('"', colonPos + 1);
    if (colonPos == std::string::npos || firstQuote == std::string::npos)
    {
        return false;
    }

    std::size_t i = firstQuote + 1;
    std::string parsed;
    while (i < text.size())
    {
        if (text[i] == '\\' && i + 1 < text.size())
        {
            const char next = text[i + 1];
            switch (next)
            {
            case 'n': parsed.push_back('\n'); break;
            case 'r': parsed.push_back('\r'); break;
            case 't': parsed.push_back('\t'); break;
            default: parsed.push_back(next); break;
            }
            i += 2;
            continue;
        }

        if (text[i] == '"')
        {
            out = parsed;
            return true;
        }

        parsed.push_back(text[i]);
        ++i;
    }

    return false;
}

bool ExtractIntValue(const std::string& text, const std::string& key, int& out)
{
    const std::string token = "\"" + key + "\"";
    const std::size_t keyPos = text.find(token);
    if (keyPos == std::string::npos)
    {
        return false;
    }

    const std::size_t colonPos = text.find(':', keyPos + token.size());
    if (colonPos == std::string::npos)
    {
        return false;
    }

    std::size_t start = colonPos + 1;
    while (start < text.size() && (text[start] == ' ' || text[start] == '\n' || text[start] == '\r' || text[start] == '\t'))
    {
        ++start;
    }

    std::size_t end = start;
    if (end < text.size() && text[end] == '-')
    {
        ++end;
    }
    while (end < text.size() && text[end] >= '0' && text[end] <= '9')
    {
        ++end;
    }

    if (end == start)
    {
        return false;
    }

    try
    {
        out = std::stoi(text.substr(start, end - start));
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool ExtractStringArray(const std::string& text, const std::string& key, std::vector<std::string>& out)
{
    const std::string token = "\"" + key + "\"";
    const std::size_t keyPos = text.find(token);
    if (keyPos == std::string::npos)
    {
        return false;
    }

    const std::size_t colonPos = text.find(':', keyPos + token.size());
    const std::size_t openBracket = text.find('[', colonPos + 1);
    const std::size_t closeBracket = text.find(']', openBracket + 1);
    if (colonPos == std::string::npos || openBracket == std::string::npos || closeBracket == std::string::npos)
    {
        return false;
    }

    std::string body = text.substr(openBracket + 1, closeBracket - openBracket - 1);
    out.clear();

    std::size_t pos = 0;
    while (pos < body.size())
    {
        const std::size_t q1 = body.find('"', pos);
        if (q1 == std::string::npos)
        {
            break;
        }
        const std::size_t q2 = body.find('"', q1 + 1);
        if (q2 == std::string::npos)
        {
            return false;
        }

        out.push_back(body.substr(q1 + 1, q2 - q1 - 1));
        pos = q2 + 1;
    }

    return true;
}

std::filesystem::path BuildSavePath(const std::string& slotName)
{
    return std::filesystem::path("saves") / (slotName + ".json");
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
    std::ifstream input(savePath);
    if (!input.is_open())
    {
        if (err)
        {
            *err = "Could not open save file: " + savePath.string();
        }
        return false;
    }

    std::ostringstream buffer;
    buffer << input.rdbuf();
    const std::string text = buffer.str();

    int version = 0;
    if (!ExtractIntValue(text, "version", version) || version != 1)
    {
        if (err)
        {
            *err = "Unsupported or missing save version in: " + savePath.string();
        }
        return false;
    }

    if (!ExtractStringValue(text, "name", outState.playerName)
        || !ExtractStringValue(text, "gender", outState.gender)
        || !ExtractIntValue(text, "hp", outState.hp)
        || !ExtractIntValue(text, "xp", outState.xp)
        || !ExtractIntValue(text, "lvl", outState.lvl)
        || !ExtractIntValue(text, "coins", outState.coins)
        || !ExtractIntValue(text, "dm", outState.dm)
        || !ExtractIntValue(text, "stamina", outState.stamina)
        || !ExtractIntValue(text, "kills", outState.kills)
        || !ExtractStringArray(text, "weapons", outState.weaponsOwnedNames)
        || !ExtractStringArray(text, "items", outState.usableItemsOwnedNames)
        || !ExtractStringValue(text, "equippedWeapon", outState.equippedWeapon))
    {
        if (err)
        {
            *err = "Save file is missing required fields: " + savePath.string();
        }
        return false;
    }

    return true;
}
