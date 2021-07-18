#pragma once
#include "ChangeClassificationTransaction.h"

class ChangeHourlyTransaction : public ChangeClassificationTransaction
{
public:
    ~ChangeHourlyTransaction() override;
    ChangeHourlyTransaction(int empId, double hourlyRate);
    ChangeHourlyTransaction(const ChangeHourlyTransaction& other) = default;
    ChangeHourlyTransaction(ChangeHourlyTransaction&& other) noexcept = default;
    ChangeHourlyTransaction& operator=(const ChangeHourlyTransaction& other) = default;
    ChangeHourlyTransaction& operator=(ChangeHourlyTransaction&& other) noexcept = default;
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsHourlyRate;
};
