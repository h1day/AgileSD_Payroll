#include "WeeklySchedule.h"
#include "Date.h"

WeeklySchedule::~WeeklySchedule() = default;

bool WeeklySchedule::IsPayDate(const Date& theDate) const
{
    return theDate.GetDayOfWeek() == Date::DayOfWeek::friday;
}

Date WeeklySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return payPeriodEndDate - 6; // The previous Saturday.
}
