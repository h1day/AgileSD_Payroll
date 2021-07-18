#include "PaydayTransaction.h"
#include "PayrollDatabase.h"
#include "PayCheck.h"
#include "Date.h"
#include "Employee.h"

#include <list>

extern PayrollDatabase g_payrollDatabase;

PaydayTransaction::~PaydayTransaction() = default;

PaydayTransaction::PaydayTransaction(const Date& payDate)
  :itsPayDate(payDate)
{
}

void PaydayTransaction::Execute()
{
  list<int> empIds;
  g_payrollDatabase.GetAllEmployeeIds(empIds);
  
  list<int>::iterator i = empIds.begin();
  for (; i != empIds.end(); i++) {
    int empId = *i;
    if (Employee* e = g_payrollDatabase.GetEmployee(empId)) {
      if (e->IsPayDate(itsPayDate)) {
	PayCheck* pc = new PayCheck(e->GetPayPeriodStartDate(itsPayDate),
				    itsPayDate);
	itsPaychecks[empId] = pc;
	e->Payday(*pc);
      }
    }
  }
}

PayCheck* PaydayTransaction::GetPaycheck(int empId)
{
  return itsPaychecks[empId];
}

int PaydayTransaction::GetPaycheckCount() const
{
  return itsPaychecks.size();
}
