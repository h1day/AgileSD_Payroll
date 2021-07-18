#pragma once
#include "ChangeMethodTransaction.h"

class ChangeHoldTransaction : public ChangeMethodTransaction
{
public:
    ~ChangeHoldTransaction() override;
    explicit ChangeHoldTransaction(int empId);
    ChangeHoldTransaction(const ChangeHoldTransaction& other) = default;
    ChangeHoldTransaction(ChangeHoldTransaction&& other) noexcept = default;
    ChangeHoldTransaction& operator=(const ChangeHoldTransaction& other) = default;
    ChangeHoldTransaction& operator=(ChangeHoldTransaction&& other) noexcept = default;
    PaymentMethod* GetMethod() const override;
};
