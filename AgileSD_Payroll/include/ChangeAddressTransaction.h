#pragma once
#include "ChangeEmployeeTransaction.h"
#include <string>

class ChangeAddressTransaction : public ChangeEmployeeTransaction
{
 public:
    ~ChangeAddressTransaction() override;
    ChangeAddressTransaction(int empId, std::string address);
    void Change(Employee& e) override;

 private:
    std::string itsAddress;
};
