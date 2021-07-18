#pragma once
#include "ChangeMethodTransaction.h"

class ChangeHoldTransaction : public ChangeMethodTransaction
{
public:
    ~ChangeHoldTransaction() override;
    explicit ChangeHoldTransaction(int empId);
    PaymentMethod* GetMethod() const override;
};
