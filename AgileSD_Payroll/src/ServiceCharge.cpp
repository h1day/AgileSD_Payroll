#include "ServiceCharge.h"

#include <utility>

ServiceCharge::~ServiceCharge() = default;

ServiceCharge::ServiceCharge(Date date, double amount)
    : itsDate(std::move(date))
      , itsAmount(amount)
{
}
