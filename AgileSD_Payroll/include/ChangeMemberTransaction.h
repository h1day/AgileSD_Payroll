#pragma once
#include "ChangeAffiliationTransaction.h"

class ChangeMemberTransaction : public ChangeAffiliationTransaction
{
public:
    ~ChangeMemberTransaction() override;
    ChangeMemberTransaction(int empId, int memberId, double dues);
    ChangeMemberTransaction(const ChangeMemberTransaction& other) = default;
    ChangeMemberTransaction(ChangeMemberTransaction&& other) noexcept = default;
    ChangeMemberTransaction& operator=(const ChangeMemberTransaction& other) = default;
    ChangeMemberTransaction& operator=(ChangeMemberTransaction&& other) noexcept = default;
    Affiliation* GetAffiliation() const override;
    void RecordMembership(Employee*) override;
private:
    int itsMemberId;
    double itsDues;
};
