#pragma once
#include "Affiliation.h"

class NoAffiliation : public Affiliation
{
public:
    ~NoAffiliation() override;
    NoAffiliation();
    NoAffiliation(const NoAffiliation& other) = default;
    NoAffiliation(NoAffiliation&& other) noexcept = default;
    NoAffiliation& operator=(const NoAffiliation& other) = default;
    NoAffiliation& operator=(NoAffiliation&& other) noexcept = default;
    double CalculateDeductions(PayCheck&) const override;
};

