#pragma once
class PayCheck;

class PaymentClassification
{
public:
    virtual ~PaymentClassification();
    PaymentClassification() = default;
    PaymentClassification(const PaymentClassification& other) = default;
    PaymentClassification(PaymentClassification&& other) noexcept = default;
    PaymentClassification& operator=(const PaymentClassification& other) = default;
    PaymentClassification& operator=(PaymentClassification&& other) noexcept = default;

    virtual double CalculatePay(PayCheck&) const = 0;
};
