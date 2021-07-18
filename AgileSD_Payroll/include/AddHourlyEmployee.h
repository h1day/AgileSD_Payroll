#pragma once
#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
public:
    ~AddHourlyEmployee() override;
    AddHourlyEmployee(int empId, std::string name, std::string address, double hourlyRate);
    AddHourlyEmployee(const AddHourlyEmployee& other) = default;
    AddHourlyEmployee(AddHourlyEmployee&& other) noexcept = default;
    AddHourlyEmployee& operator=(const AddHourlyEmployee& other) = default;
    AddHourlyEmployee& operator=(AddHourlyEmployee&& other) noexcept = default;
    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

private:
    double itsHourlyRate;
};
