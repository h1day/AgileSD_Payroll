#include "TimeCard.h"

TimeCard::~TimeCard() = default;

TimeCard::TimeCard(const Date& date, double hours)
    : itsDate(date)
      , itsHours(hours)
{
}
