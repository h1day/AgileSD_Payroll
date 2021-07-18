#include "AddHourlyEmployee.h"

#include <utility>
#include "HourlyClassification.h"
#include "WeeklySchedule.h"

AddHourlyEmployee::~AddHourlyEmployee() = default;

AddHourlyEmployee::AddHourlyEmployee(int empId, string name, string address, double hourlyRate)
  : AddEmployeeTransaction(empId, std::move(name), std::move(address))
    , itsHourlyRate(hourlyRate)
{
}

PaymentClassification* AddHourlyEmployee::GetClassification() const
{
  return new HourlyClassification(itsHourlyRate);
}

PaymentSchedule* AddHourlyEmployee::GetSchedule() const
{
  return new WeeklySchedule();
}
