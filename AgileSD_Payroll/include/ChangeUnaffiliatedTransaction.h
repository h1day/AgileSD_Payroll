#pragma once
#include "ChangeAffiliationTransaction.h"

class ChangeUnaffiliatedTransaction : public ChangeAffiliationTransaction
{
public:
    ~ChangeUnaffiliatedTransaction() override;
    explicit ChangeUnaffiliatedTransaction(int empId);
    Affiliation* GetAffiliation() const override;
    void RecordMembership(Employee*) override;
};
