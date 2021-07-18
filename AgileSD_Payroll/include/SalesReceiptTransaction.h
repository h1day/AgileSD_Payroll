#pragma once
#include "Transaction.h"
#include "Date.h"

class SalesReceiptTransaction : public Transaction
{
public:
    ~SalesReceiptTransaction() override;
    SalesReceiptTransaction(const Date& saleDate, double amount, int empId);

    void Execute() override;

private:
    int itsEmpId;
    Date itsSaleDate;
    double itsAmount;
};
