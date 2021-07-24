#include "ChangeAffiliationTransaction.h"

#include "Affiliation.h"

ChangeAffiliationTransaction::~ChangeAffiliationTransaction() = default;

ChangeAffiliationTransaction::ChangeAffiliationTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
}

void ChangeAffiliationTransaction::Change(Employee& e)
{
    auto* afBefore = e.GetAffiliation();
    afBefore->EraseMembership();

    auto* afAfter = GetAffiliation();
    afAfter->RecordMembership(e);
    e.SetAffiliation(afAfter);
}
