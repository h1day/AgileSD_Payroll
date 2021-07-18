#include "ServiceCharge.h"

ServiceCharge::~ServiceCharge() = default;

ServiceCharge::ServiceCharge(const Date& date, double amount)
    : itsDate(date)
      , itsAmount(amount)
{
}
