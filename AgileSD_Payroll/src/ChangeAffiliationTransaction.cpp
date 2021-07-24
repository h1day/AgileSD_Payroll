#include "ChangeAffiliationTransaction.h"

#include "Affiliation.h"
#include "AffiliationEraser.h"
#include "AffiliationRecorder.h"

ChangeAffiliationTransaction::~ChangeAffiliationTransaction() = default;

ChangeAffiliationTransaction::ChangeAffiliationTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
}

void ChangeAffiliationTransaction::Change(Employee& e)
{
    auto ve = AffiliationEraser();
    auto* afBefore = e.GetAffiliation();
    afBefore->Accept(ve);

    auto vr = AffiliationRecorder(e);
    auto* afAfter = GetAffiliation();
    afAfter->Accept(vr);
    e.SetAffiliation(afAfter);
}
