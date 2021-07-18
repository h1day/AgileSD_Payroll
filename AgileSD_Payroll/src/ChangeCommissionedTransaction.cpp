#include "ChangeCommissionedTransaction.h"
#include "BiweeklySchedule.h"
#include "CommissionedClassification.h"

ChangeCommissionedTransaction::~ChangeCommissionedTransaction() = default;

ChangeCommissionedTransaction::ChangeCommissionedTransaction(int empId, double salary, double rate)
: ChangeClassificationTransaction(empId)
, itsSalary(salary)
, itsRate(rate)
{
}

PaymentSchedule* ChangeCommissionedTransaction::GetSchedule() const
{
  return new BiweeklySchedule();
}

PaymentClassification* ChangeCommissionedTransaction::GetClassification() const
{
  return new CommissionedClassification(itsSalary, itsRate);
}
