#include "ChangeUnaffiliatedTransaction.h"
#include "NoAffiliation.h"

ChangeUnaffiliatedTransaction::ChangeUnaffiliatedTransaction(int empId)
    : ChangeAffiliationTransaction(empId)
{
}

Affiliation* ChangeUnaffiliatedTransaction::GetAffiliation() const
{
    return new NoAffiliation();
}
