#include "PaydayTransaction.h"
#include "PayrollDatabase.h"
#include "PayCheck.h"
#include "Date.h"
#include "Employee.h"

#include <list>

extern PayrollDatabase GpayrollDatabase;

PaydayTransaction::~PaydayTransaction() = default;

PaydayTransaction::PaydayTransaction(Date payDate)
  :itsPayDate(payDate)
{
}

void PaydayTransaction::Execute()
{
  list<int> empIds;
  GpayrollDatabase.GetAllEmployeeIds(empIds);
  
  list<int>::iterator i = empIds.begin();
  for (; i != empIds.end(); i++) {
    int empId = *i;
    if (Employee* e = GpayrollDatabase.GetEmployee(empId)) {
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
