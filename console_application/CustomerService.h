#pragma once
#include <vector>
#include <string>
#include "Customer.h"
#include "CustomerRepository.h"

class CustomerService {
public:
    explicit CustomerService(CustomerRepository& repo);

    void                  create(const Customer& c);
    std::vector<Customer> readAll();
    Customer              readById(int id);
    std::vector<Customer> readByKey(const std::string& key, const std::string& value);
    void                  update(int id, const std::string& field, const std::string& value);
    void                  remove(int id);

private:
    CustomerRepository& repo_;
};
