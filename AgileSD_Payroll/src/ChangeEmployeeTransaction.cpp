#include "ChangeEmployeeTransaction.h"
#include "Employee.h"
#include "PayrollDatabase.h"

extern PayrollDatabase g_payrollDatabase;

ChangeEmployeeTransaction::~ChangeEmployeeTransaction() = default;

ChangeEmployeeTransaction::ChangeEmployeeTransaction(int empId)
    : itsEmpId(empId)
{
}

void ChangeEmployeeTransaction::Execute()
{
    Employee* e = g_payrollDatabase.GetEmployee(itsEmpId);
    if (e != nullptr)
        Change(*e);
}
