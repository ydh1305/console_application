#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CustomerRepository {
public:
    json load();
    void save(const json& root);

private:
    static constexpr const char* FILE_PATH = "data/customers.json";
};
