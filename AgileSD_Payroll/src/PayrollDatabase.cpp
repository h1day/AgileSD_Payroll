#include "PayrollDatabase.h"
#include "Employee.h"

// ReSharper disable once CommentTypo
PayrollDatabase g_payrollDatabase;  // NOLINT(clang-diagnostic-exit-time-destructors)

PayrollDatabase::~PayrollDatabase() = default;

Employee* PayrollDatabase::GetEmployee(int empId)
{
  return itsEmployees[empId];
}

void PayrollDatabase::AddEmployee(int empId, Employee* e)
{
  itsEmployees[empId] = e;
}

void PayrollDatabase::DeleteEmployee(int empId)
{
  itsEmployees.erase(empId);
}

void PayrollDatabase::AddUnionMember(int memberId, Employee* emp)
{
  itsUnionMembers[memberId] = emp->GetEmpId();
}

void PayrollDatabase::clear()
{
  itsEmployees.clear();
  itsUnionMembers.clear();
}

Employee* PayrollDatabase::GetUnionMember(int memberId)
{
    const int empId = itsUnionMembers[memberId];
    Employee* e = itsEmployees[empId];
    return e;
}

void PayrollDatabase::RemoveUnionMember(int memberId)
{
  itsUnionMembers.erase(memberId);
}

void PayrollDatabase::GetAllEmployeeIds(list<int>& empIds)
{
  empIds.clear();
  for (auto i = itsEmployees.begin(); i != itsEmployees.end(); ++i) {
    empIds.push_back((*i).first);
  }
}


