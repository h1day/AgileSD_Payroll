#pragma once
class PayCheck;

class PaymentClassification
{
public:
    virtual ~PaymentClassification();

    virtual double CalculatePay(PayCheck&) const = 0;
};
