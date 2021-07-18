#include "ChangeUnaffiliatedTransaction.h"
#include "NoAffiliation.h"
#include "UnionAffiliation.h"
#include "PayrollDatabase.h"

extern PayrollDatabase g_payrollDatabase;

ChangeUnaffiliatedTransaction::~ChangeUnaffiliatedTransaction() = default;

ChangeUnaffiliatedTransaction::ChangeUnaffiliatedTransaction(int empId)
    : ChangeAffiliationTransaction(empId)
{
}

Affiliation* ChangeUnaffiliatedTransaction::GetAffiliation() const
{
    return new NoAffiliation();
}

void ChangeUnaffiliatedTransaction::RecordMembership(Employee* e)
{
    Affiliation* af = e->GetAffiliation();
    if (const auto uf = dynamic_cast<UnionAffiliation*>(af))
    {
        const int memberId = uf->GetMemberId();
        g_payrollDatabase.RemoveUnionMember(memberId);
    }
}
