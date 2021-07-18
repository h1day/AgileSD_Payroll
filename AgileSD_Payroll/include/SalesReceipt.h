#pragma once
#include "Date.h"

class SalesReceipt
{
public:
    virtual ~SalesReceipt() = default;
    SalesReceipt(const Date& saleDate, double amount);
    SalesReceipt(const SalesReceipt& other) = default;
    SalesReceipt(SalesReceipt&& other) noexcept = default;
    SalesReceipt& operator=(const SalesReceipt& other) = default;
    SalesReceipt& operator=(SalesReceipt&& other) noexcept = default;

    Date GetSaleDate() const { return itsSaleDate; }
    double GetAmount() const { return itsAmount; }
private:
    Date itsSaleDate;
    double itsAmount;
};
