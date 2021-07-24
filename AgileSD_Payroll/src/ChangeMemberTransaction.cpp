#include "ChangeMemberTransaction.h"
#include "UnionAffiliation.h"

ChangeMemberTransaction::~ChangeMemberTransaction() = default;

ChangeMemberTransaction::ChangeMemberTransaction(int empId, int memberId, double dues)
    : ChangeAffiliationTransaction(empId)
      , itsMemberId(memberId)
      , itsDues(dues)
{
}

Affiliation* ChangeMemberTransaction::GetAffiliation() const
{
    return new UnionAffiliation(itsMemberId, itsDues);
}
