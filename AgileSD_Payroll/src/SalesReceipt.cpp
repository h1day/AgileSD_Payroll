#include "SalesReceipt.h"

#include <utility>

SalesReceipt::SalesReceipt(Date saleDate, double amount)
    : itsSaleDate(std::move(saleDate))
      , itsAmount(amount)
{
}
