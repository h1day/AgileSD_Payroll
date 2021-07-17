#include "ChangeMailTransaction.h"
#include "MailMethod.h"

ChangeMailTransaction::~ChangeMailTransaction() = default;

ChangeMailTransaction::ChangeMailTransaction(int empid, string address)
: ChangeMethodTransaction(empid)
, itsAddress(address)
{
}

PaymentMethod* ChangeMailTransaction::GetMethod() const
{
  return new MailMethod(itsAddress);
}
