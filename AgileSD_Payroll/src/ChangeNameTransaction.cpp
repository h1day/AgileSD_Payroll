#include "ChangeNameTransaction.h"

ChangeNameTransaction::~ChangeNameTransaction() = default;

ChangeNameTransaction::ChangeNameTransaction(int empid, string name)
  : ChangeEmployeeTransaction(empid)
  , itsName(name)
{
}

void ChangeNameTransaction::Change(Employee& e)
{
  e.SetName(itsName);
}

