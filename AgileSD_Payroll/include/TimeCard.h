#pragma once
#include "Date.h"

class TimeCard
{
public:
    virtual ~TimeCard();
    TimeCard(const Date& date, double hours);
    TimeCard(const TimeCard& other) = default;
    TimeCard(TimeCard&& other) noexcept = default;
    TimeCard& operator=(const TimeCard& other) = default;
    TimeCard& operator=(TimeCard&& other) noexcept = default;

    Date GetDate() const { return itsDate; }
    double GetHours() const { return itsHours; }
private:
    Date itsDate;
    double itsHours;
};
