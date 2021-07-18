#pragma once
class PayCheck;

class PaymentMethod
{
public:
    virtual ~PaymentMethod();
    PaymentMethod() = default;
    PaymentMethod(const PaymentMethod& other) = default;
    PaymentMethod(PaymentMethod&& other) noexcept = default;
    PaymentMethod& operator=(const PaymentMethod& other) = default;
    PaymentMethod& operator=(PaymentMethod&& other) noexcept = default;

    virtual void Pay(PayCheck&) = 0;
};
