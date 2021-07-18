#pragma once
#include "ChangeClassificationTransaction.h"

class ChangeCommissionedTransaction : public ChangeClassificationTransaction
{
public:
    ~ChangeCommissionedTransaction() override;
    ChangeCommissionedTransaction(int empId, double salary, double rate);
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsSalary;
    double itsRate;
};
