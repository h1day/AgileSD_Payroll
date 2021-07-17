#include "SalesReceipt.h"

SalesReceipt::~SalesReceipt() = default;

SalesReceipt::SalesReceipt(const Date& saleDate, double amount)
: itsSaleDate(saleDate)
, itsAmount(amount)
{
}
