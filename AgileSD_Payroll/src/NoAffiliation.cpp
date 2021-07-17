#include "NoAffiliation.h"

NoAffiliation::~NoAffiliation() = default;

NoAffiliation::NoAffiliation() = default;

double NoAffiliation::CalculateDeductions(PayCheck&) const
{
  return 0;
}
