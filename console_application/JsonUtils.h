#pragma once
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// PoC: Convert any JSON value to std::string regardless of type
std::string json_value_to_string(const json& val);

// PoC: Flatten top-level object into unordered_map<string,string> (1 level deep)
std::unordered_map<std::string, std::string> json_to_flat_map(const json& j);

// PoC: Recursively flatten nested objects using "parent.child" dot-notation keys
void flatten_recursive(const json& j,
                       const std::string& prefix,
                       std::unordered_map<std::string, std::string>& out);
