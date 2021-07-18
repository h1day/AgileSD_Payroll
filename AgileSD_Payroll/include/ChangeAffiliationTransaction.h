#pragma once
#include "ChangeEmployeeTransaction.h"

class ChangeAffiliationTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeAffiliationTransaction() override;
    explicit ChangeAffiliationTransaction(int empId);
    ChangeAffiliationTransaction(const ChangeAffiliationTransaction& other) = default;
    ChangeAffiliationTransaction(ChangeAffiliationTransaction&& other) noexcept = default;
    ChangeAffiliationTransaction& operator=(const ChangeAffiliationTransaction& other) = default;
    ChangeAffiliationTransaction& operator=(ChangeAffiliationTransaction&& other) noexcept = default;
    virtual Affiliation* GetAffiliation() const = 0;
    virtual void RecordMembership(Employee*) = 0;
    void Change(Employee&) override;
};
