#pragma once
#include "ChangeClassificationTransaction.h"

class ChangeHourlyTransaction : public ChangeClassificationTransaction
{
public:
    ~ChangeHourlyTransaction() override;
    ChangeHourlyTransaction(int empId, double hourlyRate);
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsHourlyRate;
};
