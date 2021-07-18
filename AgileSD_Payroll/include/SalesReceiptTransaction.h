#pragma once
#include "Transaction.h"
#include "Date.h"

class SalesReceiptTransaction : public Transaction
{
public:
    ~SalesReceiptTransaction() override;
    SalesReceiptTransaction(const Date& saleDate, double amount, int empId);
    SalesReceiptTransaction(const SalesReceiptTransaction& other) = default;
    SalesReceiptTransaction(SalesReceiptTransaction&& other) noexcept = default;
    SalesReceiptTransaction& operator=(const SalesReceiptTransaction& other) = default;
    SalesReceiptTransaction& operator=(SalesReceiptTransaction&& other) noexcept = default;

    void Execute() override;

private:
    int itsEmpId;
    Date itsSaleDate;
    double itsAmount;
};
