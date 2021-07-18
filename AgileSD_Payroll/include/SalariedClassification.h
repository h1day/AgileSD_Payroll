#pragma once
#include "PaymentClassification.h"

class SalariedClassification : public PaymentClassification
{
public:
    ~SalariedClassification() override;
    explicit SalariedClassification(double salary);
    double GetSalary() const;

    double CalculatePay(PayCheck&) const override;

private:
    double itsSalary;
};
