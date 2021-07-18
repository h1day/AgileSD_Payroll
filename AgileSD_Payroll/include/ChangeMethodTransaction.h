#pragma once
#include "ChangeEmployeeTransaction.h"

class PaymentMethod;

class ChangeMethodTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeMethodTransaction() override;
    explicit ChangeMethodTransaction(int empId);

    virtual PaymentMethod* GetMethod() const = 0;
    void Change(Employee&) override;
};
