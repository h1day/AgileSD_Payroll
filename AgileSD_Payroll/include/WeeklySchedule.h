#pragma once

#include "PaymentSchedule.h"

class WeeklySchedule : public PaymentSchedule
{
public:
    ~WeeklySchedule() override;
    bool IsPayDate(const Date&) const override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
