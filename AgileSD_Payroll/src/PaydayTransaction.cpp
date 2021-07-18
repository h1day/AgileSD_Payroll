#include "PaydayTransaction.h"
#include "PayrollDatabase.h"
#include "PayCheck.h"
#include "Date.h"
#include "Employee.h"

#include <list>
#include <utility>

extern PayrollDatabase g_payrollDatabase;

PaydayTransaction::~PaydayTransaction() = default;

PaydayTransaction::PaydayTransaction(Date payDate)
    : itsPayDate(std::move(payDate))
{
}

void PaydayTransaction::Execute()
{
    std::list<int> empIds;
    g_payrollDatabase.GetAllEmployeeIds(empIds);

    for (auto i = empIds.begin(); i != empIds.end(); ++i)
    {
        int empId = *i;
        if (Employee* e = g_payrollDatabase.GetEmployee(empId))
        {
            if (e->IsPayDate(itsPayDate))
            {
                const auto pc = new PayCheck(e->GetPayPeriodStartDate(itsPayDate),
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
