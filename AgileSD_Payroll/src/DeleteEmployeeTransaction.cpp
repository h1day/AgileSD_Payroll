#include "DeleteEmployeeTransaction.h"
#include "PayrollDatabase.h"

extern PayrollDatabase g_payrollDatabase;
DeleteEmployeeTransaction::~DeleteEmployeeTransaction() = default;

DeleteEmployeeTransaction::DeleteEmployeeTransaction(int empId)
    : itsEmpId(empId)
{
}

void DeleteEmployeeTransaction::Execute()
{
    g_payrollDatabase.DeleteEmployee(itsEmpId);
}
