#include "ChangeDirectTransaction.h"
#include "DirectMethod.h"

ChangeDirectTransaction::~ChangeDirectTransaction() = default;

ChangeDirectTransaction::ChangeDirectTransaction(int empid, string bank, string account)
  : ChangeMethodTransaction(empid)
    , itsBank(bank)
    , itsAccount(account)
{
}

PaymentMethod* ChangeDirectTransaction::GetMethod() const
{
  return new DirectMethod(itsBank, itsAccount);
}
