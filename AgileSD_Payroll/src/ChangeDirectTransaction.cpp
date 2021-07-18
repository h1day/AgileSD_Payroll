#include "ChangeDirectTransaction.h"

#include <utility>
#include "DirectMethod.h"

ChangeDirectTransaction::~ChangeDirectTransaction() = default;

ChangeDirectTransaction::ChangeDirectTransaction(int empId, std::string bank, std::string account)
    : ChangeMethodTransaction(empId)
      , itsBank(std::move(bank))
      , itsAccount(std::move(account))
{
}

PaymentMethod* ChangeDirectTransaction::GetMethod() const
{
    return new DirectMethod(itsBank, itsAccount);
}
