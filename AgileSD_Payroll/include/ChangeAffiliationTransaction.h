#pragma once
#include "ChangeEmployeeTransaction.h"

class ChangeAffiliationTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeAffiliationTransaction() override;
    explicit ChangeAffiliationTransaction(int empId);
    virtual Affiliation* GetAffiliation() const = 0;
    virtual void RecordMembership(Employee*) = 0;
    void Change(Employee&) override;
};
