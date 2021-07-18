#pragma once
#include "ChangeEmployeeTransaction.h"

class PaymentMethod;

class ChangeMethodTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeMethodTransaction() override;
    explicit ChangeMethodTransaction(int empId);
    ChangeMethodTransaction(const ChangeMethodTransaction& other) = default;
    ChangeMethodTransaction(ChangeMethodTransaction&& other) noexcept = default;
    ChangeMethodTransaction& operator=(const ChangeMethodTransaction& other) = default;
    ChangeMethodTransaction& operator=(ChangeMethodTransaction&& other) noexcept = default;
    virtual PaymentMethod* GetMethod() const = 0;
    void Change(Employee&) override;
};
