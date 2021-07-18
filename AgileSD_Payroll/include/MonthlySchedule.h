#pragma once
#include "PaymentSchedule.h"

class MonthlySchedule : public PaymentSchedule
{
public:
    ~MonthlySchedule() override;
    MonthlySchedule() = default;
    MonthlySchedule(const MonthlySchedule& other) = default;
    MonthlySchedule(MonthlySchedule&& other) noexcept = default;
    MonthlySchedule& operator=(const MonthlySchedule& other) = default;
    MonthlySchedule& operator=(MonthlySchedule&& other) noexcept = default;

    bool IsPayDate(const Date&) const override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
