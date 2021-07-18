#include "ChangeSalariedTransaction.h"
#include "MonthlySchedule.h"
#include "SalariedClassification.h"

ChangeSalariedTransaction::~ChangeSalariedTransaction() = default;

ChangeSalariedTransaction::ChangeSalariedTransaction(int empId, double salary)
    : ChangeClassificationTransaction(empId)
      , itsSalary(salary)
{
}

PaymentSchedule* ChangeSalariedTransaction::GetSchedule() const
{
    return new MonthlySchedule();
}

PaymentClassification* ChangeSalariedTransaction::GetClassification() const
{
    return new SalariedClassification(itsSalary);
}
