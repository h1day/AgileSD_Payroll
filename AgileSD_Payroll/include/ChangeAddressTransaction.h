#pragma once
#include "ChangeEmployeeTransaction.h"
#include <string>

class ChangeAddressTransaction : public ChangeEmployeeTransaction
{
 public:
    ~ChangeAddressTransaction() override;
    ChangeAddressTransaction(int empId, std::string address);
    ChangeAddressTransaction(const ChangeAddressTransaction& other) = default;
    ChangeAddressTransaction(ChangeAddressTransaction&& other) noexcept = default;
    ChangeAddressTransaction& operator=(const ChangeAddressTransaction& other) = default;
    ChangeAddressTransaction& operator=(ChangeAddressTransaction&& other) noexcept = default;
    void Change(Employee& e) override;

 private:
    std::string itsAddress;
};
