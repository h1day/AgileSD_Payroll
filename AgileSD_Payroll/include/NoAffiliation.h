#pragma once
#include "Affiliation.h"

class NoAffiliation : public Affiliation
{
public:
    ~NoAffiliation() override;
    NoAffiliation();
    double CalculateDeductions(PayCheck&) const override;
};

