#ifndef NOAFFILIATION_H
#define NOAFFILIATION_H

#include "Affiliation.h"

class NoAffiliation : public Affiliation
{
 public:
    ~NoAffiliation() override;
  NoAffiliation();
    double CalculateDeductions(PayCheck&) const override;
};

#endif
