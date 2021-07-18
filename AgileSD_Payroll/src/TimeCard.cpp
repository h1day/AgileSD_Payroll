#include "TimeCard.h"

#include <utility>

TimeCard::~TimeCard() = default;

TimeCard::TimeCard(Date date, double hours)
    : itsDate(std::move(date))
      , itsHours(hours)
{
}
