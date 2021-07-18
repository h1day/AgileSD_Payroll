#pragma once
#include "ChangeClassificationTransaction.h"

class ChangeSalariedTransaction : public ChangeClassificationTransaction
{
public:
    ~ChangeSalariedTransaction() override;
    ChangeSalariedTransaction(int empId, double salary);
    ChangeSalariedTransaction(const ChangeSalariedTransaction& other) = default;
    ChangeSalariedTransaction(ChangeSalariedTransaction&& other) noexcept = default;
    ChangeSalariedTransaction& operator=(const ChangeSalariedTransaction& other) = default;
    ChangeSalariedTransaction& operator=(ChangeSalariedTransaction&& other) noexcept = default;
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsSalary;
};
