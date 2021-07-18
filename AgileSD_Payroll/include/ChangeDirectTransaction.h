#pragma once
#include "ChangeMethodTransaction.h"
#include <string>

class ChangeDirectTransaction : public ChangeMethodTransaction
{
public:
    ~ChangeDirectTransaction() override;
    ChangeDirectTransaction(int empId, std::string bank, std::string account);
    ChangeDirectTransaction(const ChangeDirectTransaction& other) = default;
    ChangeDirectTransaction(ChangeDirectTransaction&& other) noexcept = default;
    ChangeDirectTransaction& operator=(const ChangeDirectTransaction& other) = default;
    ChangeDirectTransaction& operator=(ChangeDirectTransaction&& other) noexcept = default;
    PaymentMethod* GetMethod() const override;
private:
    std::string itsBank;
    std::string itsAccount;
};
