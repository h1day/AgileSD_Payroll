#include "HourlyClassification.h"
#include "TimeCard.h"
#include "PayCheck.h"

HourlyClassification::~HourlyClassification() = default;

HourlyClassification::HourlyClassification(double hourlyRate)
  :itsRate(hourlyRate)
{
}

void HourlyClassification::AddTimeCard(TimeCard* tc)
{
  itsTimeCards[tc->GetDate()] = tc;
}

TimeCard* HourlyClassification::GetTimeCard(const Date& date)
{
  return itsTimeCards[date];
}

double HourlyClassification::CalculatePay(PayCheck& pc) const
{
  double totalPay = 0;
  Date payPeriodEndDate = pc.GetPayPeriodEndDate();
  for (auto i = itsTimeCards.begin(); i != itsTimeCards.end(); ++i) {
    TimeCard * tc = (*i).second;
    if (Date::IsBetween(tc->GetDate(), pc.GetPayPeriodStartDate(), pc.GetPayPeriodEndDate()))
      totalPay += CalculatePayForTimeCard(tc);
  }
  return totalPay;
}

double HourlyClassification::CalculatePayForTimeCard(TimeCard* tc) const
{
    const double hours = tc->GetHours();
    const double overtime = std::max(0.0, hours - 8.0);
    const double straightTime = hours - overtime;
    return straightTime * itsRate + overtime * itsRate * 1.5;
}
