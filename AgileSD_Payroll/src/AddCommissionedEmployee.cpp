#include "AddCommissionedEmployee.h"

#include <utility>
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"

AddCommissionedEmployee::~AddCommissionedEmployee() = default;

AddCommissionedEmployee::AddCommissionedEmployee(const int empId, std::string name, std::string address, double salary,
                                                 double commissionRate)
    : AddEmployeeTransaction(empId, std::move(name), std::move(address))
      , itsSalary(salary)
      , itsCommissionRate(commissionRate)
{
}

PaymentClassification* AddCommissionedEmployee::GetClassification() const
{
    return new CommissionedClassification(itsSalary, itsCommissionRate);
}

PaymentSchedule* AddCommissionedEmployee::GetSchedule() const
{
    return new BiweeklySchedule();
}
