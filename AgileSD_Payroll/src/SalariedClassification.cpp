#include "SalariedClassification.h"

SalariedClassification::~SalariedClassification() = default;

SalariedClassification::SalariedClassification(double salary)
    : itsSalary(salary)
{
}

double SalariedClassification::GetSalary() const
{
    return itsSalary;
}

double SalariedClassification::CalculatePay(PayCheck&) const
{
    return itsSalary;
}
