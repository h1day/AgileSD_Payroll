#include "NoAffiliation.h"
#include "AffiliationVisitor.h"

double NoAffiliation::CalculateDeductions(PayCheck&) const
{
    return 0;
}

void NoAffiliation::Accept(AffiliationVisitor& v)
{
    v.visit(*this);
}
