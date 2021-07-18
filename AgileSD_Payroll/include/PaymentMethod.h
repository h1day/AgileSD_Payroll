#pragma once
class PayCheck;

class PaymentMethod
{
public:
    virtual ~PaymentMethod();

    virtual void Pay(PayCheck&) = 0;
};
