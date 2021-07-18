#pragma once
#include "AddEmployeeTransaction.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
public:
    ~AddSalariedEmployee() override;
    AddSalariedEmployee(int empId, std::string name, std::string address, double salary);
    AddSalariedEmployee(const AddSalariedEmployee& other) = default;
    AddSalariedEmployee(AddSalariedEmployee&& other) noexcept = default;
    AddSalariedEmployee& operator=(const AddSalariedEmployee& other) = default;
    AddSalariedEmployee& operator=(AddSalariedEmployee&& other) noexcept = default;
    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

private:
    double itsSalary;
};
