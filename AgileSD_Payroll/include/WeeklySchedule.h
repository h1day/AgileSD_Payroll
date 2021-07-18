#pragma once

#include "PaymentSchedule.h"

class WeeklySchedule : public PaymentSchedule
{
public:
    ~WeeklySchedule() override;
    WeeklySchedule() = default;
    WeeklySchedule(const WeeklySchedule& other) = default;
    WeeklySchedule(WeeklySchedule&& other) noexcept = default;
    WeeklySchedule& operator=(const WeeklySchedule& other) = default;
    WeeklySchedule& operator=(WeeklySchedule&& other) noexcept = default;

    bool IsPayDate(const Date&) const override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
