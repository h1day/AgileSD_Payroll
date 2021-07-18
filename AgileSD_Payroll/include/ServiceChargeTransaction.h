#pragma once
#include "Transaction.h"
#include "Date.h"

class ServiceChargeTransaction : public Transaction
{
public:
    ~ServiceChargeTransaction() override;
    ServiceChargeTransaction(int memberId, const Date& date, double charge);
    void Execute() override;

private:
    int itsMemberId;
    Date itsDate;
    double itsCharge;
};
