#pragma once
#include "PaymentMethod.h"

class HoldMethod : public PaymentMethod
{
public:
    ~HoldMethod() override;

    void Pay(PayCheck&) override;
};
