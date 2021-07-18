#pragma once
#include "PaymentSchedule.h"

class MonthlySchedule : public PaymentSchedule
{
public:
    ~MonthlySchedule() override;

    bool IsPayDate(const Date&) const override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
