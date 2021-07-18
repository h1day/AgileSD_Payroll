#pragma once
#include "Date.h"

class ServiceCharge
{
public:
    ~ServiceCharge();
    ServiceCharge(const Date& date, double amount);
    double GetAmount() const { return itsAmount; }
    Date GetDate() const { return itsDate; }
private:
    Date itsDate;
    double itsAmount;
};
