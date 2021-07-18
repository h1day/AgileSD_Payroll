#include "AddSalariedEmployee.h"

#include <utility>
#include "SalariedClassification.h"
#include "MonthlySchedule.h"

AddSalariedEmployee::~AddSalariedEmployee() = default;

AddSalariedEmployee::AddSalariedEmployee(const int empId, string name, string address, double salary)
  : AddEmployeeTransaction(empId, std::move(name), std::move(address))
    , itsSalary(salary)
{
}

PaymentClassification* AddSalariedEmployee::GetClassification() const
{
  return new SalariedClassification(itsSalary);
}

PaymentSchedule* AddSalariedEmployee::GetSchedule() const
{
  return new MonthlySchedule();
}
