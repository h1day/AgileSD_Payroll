#include "ServiceChargeTransaction.h"

#include <utility>
#include "Employee.h"
#include "ServiceCharge.h"
#include "PayrollDatabase.h"
#include "UnionAffiliation.h"

extern PayrollDatabase g_payrollDatabase;

ServiceChargeTransaction::~ServiceChargeTransaction() = default;

ServiceChargeTransaction::ServiceChargeTransaction(int memberId, Date date, double charge)
    : itsMemberId(memberId)
      , itsDate(std::move(date))
      , itsCharge(charge)
{
}

void ServiceChargeTransaction::Execute()
{
    Employee* e = g_payrollDatabase.GetUnionMember(itsMemberId);
    Affiliation* af = e->GetAffiliation();
    if (auto uaf = dynamic_cast<UnionAffiliation*>(af))
    {
        uaf->AddServiceCharge(itsDate, itsCharge);
    }
}
