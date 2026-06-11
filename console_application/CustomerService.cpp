#include "CustomerService.h"
#include "JsonUtils.h"
#include <stdexcept>

CustomerService::CustomerService(CustomerRepository& repo) : repo_(repo) {}

void CustomerService::create(const Customer& c)
{
    json root = repo_.load();

    Customer newCustomer  = c;
    newCustomer.id        = root.at("next_id").get<int>();
    root["next_id"]       = newCustomer.id + 1;
    root["customers"].push_back(to_json(newCustomer));

    repo_.save(root);
}

std::vector<Customer> CustomerService::readAll()
{
    json root = repo_.load();
    std::vector<Customer> result;

    for (const auto& item : root.at("customers"))
        result.push_back(from_json(item));

    return result;
}

Customer CustomerService::readById(int id)
{
    json root = repo_.load();

    for (const auto& item : root.at("customers"))
    {
        if (item.at("id").get<int>() == id)
            return from_json(item);
    }

    throw std::runtime_error("ID " + std::to_string(id) + "에 해당하는 고객이 없습니다.");
}

std::vector<Customer> CustomerService::readByKey(const std::string& key, const std::string& value)
{
    json root = repo_.load();
    std::vector<Customer> result;

    for (const auto& item : root.at("customers"))
    {
        auto flat = json_to_flat_map(item);
        if (flat.count(key) && flat.at(key) == value)
            result.push_back(from_json(item));
    }

    return result;
}

void CustomerService::update(int id, const std::string& field, const std::string& value)
{
    json root = repo_.load();

    for (auto& item : root.at("customers"))
    {
        if (item.at("id").get<int>() == id)
        {
            item[field] = value;
            repo_.save(root);
            return;
        }
    }

    throw std::runtime_error("ID " + std::to_string(id) + "에 해당하는 고객이 없습니다.");
}

void CustomerService::remove(int id)
{
    json root = repo_.load();
    auto& customers = root.at("customers");

    for (auto it = customers.begin(); it != customers.end(); ++it)
    {
        if (it->at("id").get<int>() == id)
        {
            customers.erase(it);
            repo_.save(root);
            return;
        }
    }

    throw std::runtime_error("ID " + std::to_string(id) + "에 해당하는 고객이 없습니다.");
}
