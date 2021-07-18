#pragma once
#include "PaymentSchedule.h"

class BiweeklySchedule : public PaymentSchedule
{
public:
	~BiweeklySchedule() override;
    BiweeklySchedule() = default;
    BiweeklySchedule(const BiweeklySchedule& other) = default;
    BiweeklySchedule(BiweeklySchedule&& other) noexcept = default;
    BiweeklySchedule& operator=(const BiweeklySchedule& other) = default;
    BiweeklySchedule& operator=(BiweeklySchedule&& other) noexcept = default;
	bool IsPayDate(const Date&) const override;
	Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
