#include "ChangeAddressTransaction.h"

#include <utility>

ChangeAddressTransaction::~ChangeAddressTransaction() = default;

ChangeAddressTransaction::ChangeAddressTransaction(int empId, std::string address)
  : ChangeEmployeeTransaction(empId)
    , itsAddress(std::move(address))
{
}

void ChangeAddressTransaction::Change(Employee& e)
{
  e.SetAddress(itsAddress);
}
