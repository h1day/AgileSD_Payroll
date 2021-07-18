#pragma once
#include "PaymentMethod.h"

class HoldMethod : public PaymentMethod
{
public:
    ~HoldMethod() override;
    HoldMethod() = default;
    HoldMethod(const HoldMethod& other) = default;
    HoldMethod(HoldMethod&& other) noexcept = default;
    HoldMethod& operator=(const HoldMethod& other) = default;
    HoldMethod& operator=(HoldMethod&& other) noexcept = default;

    void Pay(PayCheck&) override;
};
