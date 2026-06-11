#include "JsonUtils.h"
#include <stdexcept>

std::string json_value_to_string(const json& val)
{
    if (val.is_string())  return val.get<std::string>();
    if (val.is_number())  return val.dump();
    if (val.is_boolean()) return val.get<bool>() ? "true" : "false";
    if (val.is_null())    return "null";
    return val.dump(); // object / array -> serialized JSON string
}

std::unordered_map<std::string, std::string> json_to_flat_map(const json& j)
{
    if (!j.is_object())
        throw std::invalid_argument("Root JSON is not an object.");

    std::unordered_map<std::string, std::string> result;
    for (auto& [key, val] : j.items())
        result[key] = json_value_to_string(val);
    return result;
}

void flatten_recursive(const json& j,
                       const std::string& prefix,
                       std::unordered_map<std::string, std::string>& out)
{
    for (auto& [key, val] : j.items())
    {
        std::string full_key = prefix.empty() ? key : prefix + "." + key;
        if (val.is_object())
            flatten_recursive(val, full_key, out);
        else
            out[full_key] = json_value_to_string(val);
    }
}
