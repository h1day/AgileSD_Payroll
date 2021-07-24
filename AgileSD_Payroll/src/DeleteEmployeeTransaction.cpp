#include "DeleteEmployeeTransaction.h"

#include "Employee.h"
#include "PayrollDatabase.h"

extern PayrollDatabase g_payrollDatabase;
DeleteEmployeeTransaction::~DeleteEmployeeTransaction() = default;

DeleteEmployeeTransaction::DeleteEmployeeTransaction(int empId)
    : itsEmpId(empId)
{
}

void DeleteEmployeeTransaction::Execute()
{
    const auto e = g_payrollDatabase.GetEmployee(itsEmpId);
    g_payrollDatabase.DeleteEmployee(itsEmpId);
    delete e;
}
