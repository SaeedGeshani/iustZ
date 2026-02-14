#pragma once

#include <cctype>
#include <istream>
#include <map>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace nlohmann
{
class json
{
public:
    struct parse_error : std::runtime_error
    {
        explicit parse_error(const std::string& message) : std::runtime_error(message) {}
    };

    using object_t = std::map<std::string, json>;
    using array_t = std::vector<json>;
    using const_iterator = object_t::const_iterator;

    json() : value_(object_t{}) {}

    bool is_object() const { return std::holds_alternative<object_t>(value_); }
    bool is_array() const { return std::holds_alternative<array_t>(value_); }
    bool is_string() const { return std::holds_alternative<std::string>(value_); }
    bool is_number_integer() const { return std::holds_alternative<long long>(value_); }

    const object_t* as_object() const { return std::get_if<object_t>(&value_); }
    const array_t* as_array() const { return std::get_if<array_t>(&value_); }

    const_iterator find(const std::string& key) const
    {
        static const object_t empty;
        const object_t* object = as_object();
        if (!object)
        {
            return empty.end();
        }
        return object->find(key);
    }

    const_iterator end() const
    {
        static const object_t empty;
        const object_t* object = as_object();
        if (!object)
        {
            return empty.end();
        }
        return object->end();
    }

    template <typename T>
    T get() const;

    friend std::istream& operator>>(std::istream& in, json& out)
    {
        std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        std::size_t pos = 0;
        out = parseValue(text, pos);
        skipWs(text, pos);
        if (pos != text.size())
        {
            throw parse_error("Unexpected trailing input");
        }
        return in;
    }

private:
    std::variant<object_t, array_t, std::string, long long> value_;

    static void skipWs(const std::string& s, std::size_t& pos)
    {
        while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos])))
        {
            ++pos;
        }
    }

    static void require(bool condition, const std::string& message)
    {
        if (!condition)
        {
            throw parse_error(message);
        }
    }

    static std::string parseString(const std::string& s, std::size_t& pos)
    {
        require(pos < s.size() && s[pos] == '"', "Expected string");
        ++pos;
        std::string out;
        while (pos < s.size())
        {
            char c = s[pos++];
            if (c == '"')
            {
                return out;
            }
            if (c == '\\')
            {
                require(pos < s.size(), "Invalid escape");
                char esc = s[pos++];
                switch (esc)
                {
                case '"': out.push_back('"'); break;
                case '\\': out.push_back('\\'); break;
                case '/': out.push_back('/'); break;
                case 'b': out.push_back('\b'); break;
                case 'f': out.push_back('\f'); break;
                case 'n': out.push_back('\n'); break;
                case 'r': out.push_back('\r'); break;
                case 't': out.push_back('\t'); break;
                default: throw parse_error("Unsupported escape");
                }
                continue;
            }
            out.push_back(c);
        }
        throw parse_error("Unterminated string");
    }

    static long long parseInteger(const std::string& s, std::size_t& pos)
    {
        std::size_t start = pos;
        if (s[pos] == '-')
        {
            ++pos;
        }
        require(pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos])), "Expected integer");
        while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos])))
        {
            ++pos;
        }
        if (pos < s.size() && (s[pos] == '.' || s[pos] == 'e' || s[pos] == 'E'))
        {
            throw parse_error("Only integer values supported");
        }
        return std::stoll(s.substr(start, pos - start));
    }

    static json parseObject(const std::string& s, std::size_t& pos)
    {
        require(s[pos] == '{', "Expected object");
        ++pos;
        object_t obj;
        skipWs(s, pos);
        if (pos < s.size() && s[pos] == '}')
        {
            ++pos;
            json j;
            j.value_ = std::move(obj);
            return j;
        }

        while (true)
        {
            skipWs(s, pos);
            std::string key = parseString(s, pos);
            skipWs(s, pos);
            require(pos < s.size() && s[pos] == ':', "Expected ':'");
            ++pos;
            skipWs(s, pos);
            obj[key] = parseValue(s, pos);
            skipWs(s, pos);
            require(pos < s.size(), "Unterminated object");
            if (s[pos] == '}')
            {
                ++pos;
                break;
            }
            require(s[pos] == ',', "Expected ','");
            ++pos;
        }

        json j;
        j.value_ = std::move(obj);
        return j;
    }

    static json parseArray(const std::string& s, std::size_t& pos)
    {
        require(s[pos] == '[', "Expected array");
        ++pos;
        array_t arr;
        skipWs(s, pos);
        if (pos < s.size() && s[pos] == ']')
        {
            ++pos;
            json j;
            j.value_ = std::move(arr);
            return j;
        }

        while (true)
        {
            skipWs(s, pos);
            arr.push_back(parseValue(s, pos));
            skipWs(s, pos);
            require(pos < s.size(), "Unterminated array");
            if (s[pos] == ']')
            {
                ++pos;
                break;
            }
            require(s[pos] == ',', "Expected ','");
            ++pos;
        }

        json j;
        j.value_ = std::move(arr);
        return j;
    }

    static json parseValue(const std::string& s, std::size_t& pos)
    {
        skipWs(s, pos);
        require(pos < s.size(), "Unexpected end");

        if (s[pos] == '{')
        {
            return parseObject(s, pos);
        }
        if (s[pos] == '[')
        {
            return parseArray(s, pos);
        }
        if (s[pos] == '"')
        {
            json j;
            j.value_ = parseString(s, pos);
            return j;
        }

        json j;
        j.value_ = parseInteger(s, pos);
        return j;
    }
};

template <>
inline int json::get<int>() const
{
    return static_cast<int>(std::get<long long>(value_));
}

template <>
inline std::string json::get<std::string>() const
{
    return std::get<std::string>(value_);
}

} // namespace nlohmann
