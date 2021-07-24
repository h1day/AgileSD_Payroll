#include "NoAffiliation.h"

NoAffiliation::~NoAffiliation() = default;

NoAffiliation::NoAffiliation() = default;

void NoAffiliation::EraseMembership()
{
}

void NoAffiliation::RecordMembership(Employee& e)
{
}

double NoAffiliation::CalculateDeductions(PayCheck&) const
{
    return 0;
}
