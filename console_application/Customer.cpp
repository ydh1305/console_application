#include "Customer.h"

Customer from_json(const json& j)
{
    Customer c;
    c.id         = j.at("id").get<int>();
    c.name       = j.at("name").get<std::string>();
    c.email      = j.at("email").get<std::string>();
    c.phone      = j.at("phone").get<std::string>();
    c.address    = j.at("address").get<std::string>();
    c.created_at = j.at("created_at").get<std::string>();
    return c;
}

json to_json(const Customer& c)
{
    json j;
    j["id"]         = c.id;
    j["name"]       = c.name;
    j["email"]      = c.email;
    j["phone"]      = c.phone;
    j["address"]    = c.address;
    j["created_at"] = c.created_at;
    return j;
}
