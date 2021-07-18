#pragma once
#include "AddEmployeeTransaction.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
public:
    ~AddSalariedEmployee() override;
    AddSalariedEmployee(int empId, std::string name, std::string address, double salary);
    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

private:
    double itsSalary;
};
