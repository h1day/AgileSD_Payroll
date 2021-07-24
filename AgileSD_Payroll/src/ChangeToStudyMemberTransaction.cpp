#include "ChangeToStudyMemberTransaction.h"
#include "StudyAffiliation.h"

ChangeToStudyMemberTransaction::~ChangeToStudyMemberTransaction() = default;

ChangeToStudyMemberTransaction::ChangeToStudyMemberTransaction(int empId, int memberId, double dues)
    : ChangeAffiliationTransaction(empId)
      , itsMemberId(memberId)
      , itsDues(dues)
{
}

Affiliation* ChangeToStudyMemberTransaction::GetAffiliation() const
{
    return new StudyAffiliation(itsMemberId, itsDues);
}
