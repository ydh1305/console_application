#pragma once
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Customer {
    int         id;
    std::string name;
    std::string email;
    std::string phone;
    std::string address;
    std::string created_at;
};

Customer    from_json(const json& j);
json        to_json(const Customer& c);
