#pragma once
#include "ChangeAffiliationTransaction.h"

class ChangeToStudyMemberTransaction : public ChangeAffiliationTransaction
{
public:
    ~ChangeToStudyMemberTransaction() override;
    ChangeToStudyMemberTransaction(int empId, int memberId, double dues);
    ChangeToStudyMemberTransaction(const ChangeToStudyMemberTransaction& other) = default;
    ChangeToStudyMemberTransaction(ChangeToStudyMemberTransaction&& other) noexcept = default;
    ChangeToStudyMemberTransaction& operator=(const ChangeToStudyMemberTransaction& other) = default;
    ChangeToStudyMemberTransaction& operator=(ChangeToStudyMemberTransaction&& other) noexcept = default;
    Affiliation* GetAffiliation() const override;
private:
    int itsMemberId;
    double itsDues;
};
