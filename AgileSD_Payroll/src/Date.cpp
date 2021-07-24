#include "Date.h"
#include <iostream>

long Date::secondsPerDay = 60L * 60L * 24L;

Date::Date()
{
    time_t now = time(nullptr);
    const errno_t err = localtime_s(&itsTimeStruct, &now);
    if (err)
    {
        throw;
    }
    itsTimeStruct.tm_sec = 0;
    itsTimeStruct.tm_min = 0;
    itsTimeStruct.tm_hour = 12;
    itsTime = mktime(&itsTimeStruct);
}

Date::Date(int month, int day, int year)
{
    memset(&itsTimeStruct, 0, sizeof(itsTimeStruct));
    itsTimeStruct.tm_mon = month - 1;
    itsTimeStruct.tm_mday = day;
    itsTimeStruct.tm_year = year - 1900;
    itsTimeStruct.tm_sec = 0;
    itsTimeStruct.tm_min = 0;
    itsTimeStruct.tm_hour = 12;
    itsTime = mktime(&itsTimeStruct);
    const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
    if (err)
    {
        throw;
    }
}

Date::Date(const Date& theDate)
{
    *this = theDate;
}

Date& Date::operator=(const Date& theDate)
{
    itsTime = theDate.itsTime;
    const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
    if (err)
    {
        throw;
    }
    return *this;
}

int Date::GetMonth() const { return itsTimeStruct.tm_mon + 1; }
int Date::GetDay() const { return itsTimeStruct.tm_mday; }
int Date::GetYear() const { return itsTimeStruct.tm_year + 1900; }

Date::DayOfWeek Date::GetDayOfWeek() const
{
    return static_cast<DayOfWeek>(itsTimeStruct.tm_wday);
}

std::string Date::GetDayOfWeekName() const
{
    std::string retVal;
    switch (GetDayOfWeek())
    {
    case DayOfWeek::sunday:
        retVal = "Sunday";
        break;
    case DayOfWeek::monday:
        retVal = "Monday";
        break;
    case DayOfWeek::tuesday:
        retVal = "Tuesday";
        break;
    case DayOfWeek::wednesday:
        retVal = "Wednesday";
        break;
    case DayOfWeek::thursday:
        retVal = "Thursday";
        break;
    case DayOfWeek::friday:
        retVal = "Friday";
        break;
    case DayOfWeek::saturday:
        retVal = "Saturday";
        break;
    }
    return retVal;
}

// char operator<<(const std::ostream& lhs, int rhs)
// {
//     char dummy = 0;
//     return dummy;
// }

std::ostream& operator<<(std::ostream& o, const Date& theDate)
{
    o << theDate.GetMonth() << '/'
        << theDate.GetDay() << '/'
        << theDate.GetYear();
    return o;
}

// char operator>>(const std::istream& lhs, int rhs)
// {
//     char dummy = 0;
//     return dummy;
// }

std::istream& operator>>(std::istream& i, Date& theDate)
{
    int month, day, year;
    char slash;
    i >> month >> slash >> day >> slash >> year;
    const Date tmp(month, day, year);
    theDate = tmp;
    return i;
}

int Date::operator==(const Date& theDate) const
{
    return itsTime == theDate.itsTime;
}

int Date::operator!=(const Date& theDate) const
{
    return itsTime != theDate.itsTime;
}

int Date::operator<(const Date& theDate) const
{
    return itsTime < theDate.itsTime;
}

int Date::operator>(const Date& theDate) const
{
    return itsTime > theDate.itsTime;
}

int Date::operator<=(const Date& theDate) const
{
    return itsTime <= theDate.itsTime;
}

int Date::operator>=(const Date& theDate) const
{
    return itsTime >= theDate.itsTime;
}

Date operator+(int days, const Date& theDate)
{
    Date retVal = theDate;
    retVal += days;
    return retVal;
}

Date operator+(const Date& theDate, int days)
{
    return days + theDate;
}

Date Date::operator-(int days) const
{
    Date retVal = *this;
    retVal -= days;
    return retVal;
}

int Date::operator-(const Date& theDate) const
{
    return static_cast<int>((itsTime - theDate.itsTime) / static_cast<time_t>(secondsPerDay));
}

Date& Date::operator+=(int days)
{
    itsTime += static_cast<time_t>(days) * secondsPerDay;
    const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
    if (err)
    {
        throw;
    }
    return *this;
}

Date& Date::operator-=(int days)
{
    itsTime -= static_cast<time_t>(days) * secondsPerDay;
    const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
    if (err)
    {
        throw;
    }
    return *this;
}

Date& Date::operator++()
{
    return ((*this) += 1);
}

Date Date::operator++(int) // postfix
{
    Date retVal = *this;
    (*this) += 1;
    return retVal;
}

Date& Date::operator--()
{
    return ((*this) -= 1);
}

Date Date::operator--(int) // postfix
{
    Date retVal = *this;
    (*this) -= 1;
    return retVal;
}
