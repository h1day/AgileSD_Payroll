#ifndef BIWEEKLYSCHEDULE_H
#define BIWEEKLYSCHEDULE_H

#include "PaymentSchedule.h"

class BiweeklySchedule : public PaymentSchedule
{
public:
	~BiweeklySchedule() override;
	bool IsPayDate(const Date&) const override;
	Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const override;
};
#endif
