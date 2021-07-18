#pragma once
#include "PaymentClassification.h"

class SalariedClassification : public PaymentClassification
{
public:
    ~SalariedClassification() override;
    explicit SalariedClassification(double salary);
    SalariedClassification(const SalariedClassification& other) = default;
    SalariedClassification(SalariedClassification&& other) noexcept = default;
    SalariedClassification& operator=(const SalariedClassification& other) = default;
    SalariedClassification& operator=(SalariedClassification&& other) noexcept = default;

    double GetSalary() const;

    double CalculatePay(PayCheck&) const override;

private:
    double itsSalary;
};
