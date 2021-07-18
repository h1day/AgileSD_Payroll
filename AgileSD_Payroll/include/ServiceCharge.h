#pragma once
#include "Date.h"

class ServiceCharge
{
public:
    ~ServiceCharge();
    ServiceCharge(const Date& date, double amount);
    ServiceCharge(const ServiceCharge& other) = default;
    ServiceCharge(ServiceCharge&& other) noexcept = default;
    ServiceCharge& operator=(const ServiceCharge& other) = default;
    ServiceCharge& operator=(ServiceCharge&& other) noexcept = default;

    double GetAmount() const { return itsAmount; }
    Date GetDate() const { return itsDate; }
private:
    Date itsDate;
    double itsAmount;
};
