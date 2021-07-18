#include "ChangeMethodTransaction.h"

ChangeMethodTransaction::~ChangeMethodTransaction() = default;

ChangeMethodTransaction::ChangeMethodTransaction(int empId)
: ChangeEmployeeTransaction(empId)
{
}

void ChangeMethodTransaction::Change(Employee& e)
{
  e.SetMethod(GetMethod());
}
