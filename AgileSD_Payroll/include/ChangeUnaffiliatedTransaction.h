#pragma once
#include "ChangeAffiliationTransaction.h"

class ChangeUnaffiliatedTransaction : public ChangeAffiliationTransaction
{
public:
    ~ChangeUnaffiliatedTransaction() override = default;
    explicit ChangeUnaffiliatedTransaction(int empId);
    ChangeUnaffiliatedTransaction(const ChangeUnaffiliatedTransaction& other) = default;
    ChangeUnaffiliatedTransaction(ChangeUnaffiliatedTransaction&& other) noexcept = default;
    ChangeUnaffiliatedTransaction& operator=(const ChangeUnaffiliatedTransaction& other) = default;
    ChangeUnaffiliatedTransaction& operator=(ChangeUnaffiliatedTransaction&& other) noexcept = default;

    Affiliation* GetAffiliation() const override;
};
