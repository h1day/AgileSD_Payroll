#pragma once
#include "ChangeClassificationTransaction.h"

class ChangeSalariedTransaction : public ChangeClassificationTransaction
{
public:
    ~ChangeSalariedTransaction() override;
    ChangeSalariedTransaction(int empId, double salary);
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsSalary;
};
