#pragma once
class Date;

class PaymentSchedule
{
public:
    virtual ~PaymentSchedule();
    PaymentSchedule() = default;
    PaymentSchedule(const PaymentSchedule& other) = default;
    PaymentSchedule(PaymentSchedule&& other) noexcept = default;
    PaymentSchedule& operator=(const PaymentSchedule& other) = default;
    PaymentSchedule& operator=(PaymentSchedule&& other) noexcept = default;

    virtual bool IsPayDate(const Date&) const = 0;
    virtual Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const = 0;
};
