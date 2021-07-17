#include "UnionAffiliation.h"
#include "ServiceCharge.h"
#include "Date.h"
#include "PayCheck.h"

UnionAffiliation::UnionAffiliation(int memberId, double dues)
: itsMemberId(memberId)
, itsDues(dues)
{
}

ServiceCharge* UnionAffiliation::GetServiceCharge(const Date& date)
{
  return itsServiceCharges[date];
}

void UnionAffiliation::AddServiceCharge(const Date& date, double amount)
{
  auto* sc = new ServiceCharge(date, amount);
  itsServiceCharges[date] = sc;
}

namespace
{
  int NumberOfFridaysInPayPeriod(const Date& payPeriodStart,
				 const Date& payPeriodEnd)
  {
    int fridays = 0;
    for (Date day = payPeriodStart; day <= payPeriodEnd; ++day) {
      if (day.GetDayOfWeek() == Date::DayOfWeek::friday)
	fridays++;
    }
    return fridays;
  }
}

double UnionAffiliation::CalculateDeductions(Paycheck& pc) const
{
  double totalServiceCharge = 0;

  for (auto i=itsServiceCharges.begin(); i != itsServiceCharges.end(); ++i) {
    ServiceCharge* sc = (*i).second;
    if (Date::IsBetween(sc->GetDate(), pc.GetPayPeriodStartDate(), pc.GetPayPeriodEndDate()))
      totalServiceCharge += sc->GetAmount();
  }
  const int fridays = NumberOfFridaysInPayPeriod(pc.GetPayPeriodStartDate(),
					   pc.GetPayPeriodEndDate());
  const double totalDues = itsDues * fridays;
  return totalDues + totalServiceCharge;
}
