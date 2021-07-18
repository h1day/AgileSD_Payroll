#pragma once
#include "AddEmployeeTransaction.h"

class AddCommissionedEmployee : public AddEmployeeTransaction
{
public:
    ~AddCommissionedEmployee() override;
    AddCommissionedEmployee(int empId, std::string name, std::string address, double salary, double commissionRate);
    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

private:
    double itsSalary;
    double itsCommissionRate;
};
