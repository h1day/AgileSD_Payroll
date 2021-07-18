#include "ChangeNameTransaction.h"

#include <utility>

ChangeNameTransaction::~ChangeNameTransaction() = default;

ChangeNameTransaction::ChangeNameTransaction(int empId, std::string name)
    : ChangeEmployeeTransaction(empId)
      , itsName(std::move(name))
{
}

void ChangeNameTransaction::Change(Employee& e)
{
    e.SetName(itsName);
}
