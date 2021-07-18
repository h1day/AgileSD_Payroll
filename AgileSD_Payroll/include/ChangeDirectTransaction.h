#pragma once
#include "ChangeMethodTransaction.h"
#include <string>

class ChangeDirectTransaction : public ChangeMethodTransaction
{
public:
    ~ChangeDirectTransaction() override;
    ChangeDirectTransaction(int empId, std::string bank, std::string account);
    PaymentMethod* GetMethod() const override;
private:
    std::string itsBank;
    std::string itsAccount;
};
