#include "StudyAffiliation.h"

#include "AffiliationVisitor.h"
#include "PayCheck.h"

StudyAffiliation::~StudyAffiliation() = default;


StudyAffiliation::StudyAffiliation(int memberId, double dues)
    : itsMemberId(memberId)
      , itsDues(dues)
{
}

double StudyAffiliation::CalculateDeductions(PayCheck& pc) const
{
    return itsDues + 100.0;
}

void StudyAffiliation::Accept(AffiliationVisitor& v)
{
    v.visit(*this);
}
