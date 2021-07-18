#include "ChangeMailTransaction.h"

#include <utility>
#include "MailMethod.h"

ChangeMailTransaction::~ChangeMailTransaction() = default;

ChangeMailTransaction::ChangeMailTransaction(int empId, std::string address)
: ChangeMethodTransaction(empId)
, itsAddress(std::move(address))
{
}

PaymentMethod* ChangeMailTransaction::GetMethod() const
{
  return new MailMethod(itsAddress);
}
