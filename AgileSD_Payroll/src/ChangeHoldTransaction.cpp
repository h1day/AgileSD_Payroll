#include "ChangeHoldTransaction.h"
#include "HoldMethod.h"

ChangeHoldTransaction::~ChangeHoldTransaction() = default;

ChangeHoldTransaction::ChangeHoldTransaction(int empId)
    : ChangeMethodTransaction(empId)
{
}

PaymentMethod* ChangeHoldTransaction::GetMethod() const
{
    return new HoldMethod();
}
