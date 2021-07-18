#pragma once
#include "ChangeClassificationTransaction.h"

class ChangeCommissionedTransaction : public ChangeClassificationTransaction
{
public:
    ~ChangeCommissionedTransaction() override;
    ChangeCommissionedTransaction(int empId, double salary, double rate);
    ChangeCommissionedTransaction(const ChangeCommissionedTransaction& other) = default;
    ChangeCommissionedTransaction(ChangeCommissionedTransaction&& other) noexcept = default;
    ChangeCommissionedTransaction& operator=(const ChangeCommissionedTransaction& other) = default;
    ChangeCommissionedTransaction& operator=(ChangeCommissionedTransaction&& other) noexcept = default;
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsSalary;
    double itsRate;
};
