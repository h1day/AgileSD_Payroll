#pragma once
#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
public:
    ~AddHourlyEmployee() override;
    AddHourlyEmployee(int empId, std::string name, std::string address, double hourlyRate);
    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

private:
    double itsHourlyRate;
};
