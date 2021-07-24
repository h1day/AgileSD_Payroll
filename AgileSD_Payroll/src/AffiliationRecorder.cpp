#include "AffiliationRecorder.h"
#include "UnionAffiliation.h"
#include "PayrollDatabase.h"

extern PayrollDatabase g_payrollDatabase;

AffiliationRecorder::AffiliationRecorder(Employee& e)
    : AffiliationVisitor(),
      itsEmployee(&e)
{
}

void AffiliationRecorder::visit(NoAffiliation& a)
{
    //do nothing
}

void AffiliationRecorder::visit(UnionAffiliation& a)
{
    const int memberId = a.GetMemberId();
    g_payrollDatabase.RemoveUnionMember(memberId);
    g_payrollDatabase.AddUnionMember(memberId, itsEmployee);
}
