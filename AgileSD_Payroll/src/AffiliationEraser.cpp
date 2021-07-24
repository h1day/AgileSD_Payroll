#include "AffiliationEraser.h"
#include "StudyAffiliation.h"
#include "UnionAffiliation.h"
#include "PayrollDatabase.h"

extern PayrollDatabase g_payrollDatabase;

 void AffiliationEraser::visit(NoAffiliation& a)
 {
     //do nothing
 }

void AffiliationEraser::visit(UnionAffiliation& a)
{
    const int memberId = a.GetMemberId();
    g_payrollDatabase.RemoveUnionMember(memberId);
}

void AffiliationEraser::visit(StudyAffiliation& a)
{
    const int memberId = a.GetMemberId();
    g_payrollDatabase.RemoveStudyMember(memberId);
}