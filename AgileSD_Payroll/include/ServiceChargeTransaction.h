#pragma once
#include "Transaction.h"
#include "Date.h"

class ServiceChargeTransaction : public Transaction
{
public:
    ~ServiceChargeTransaction() override;
    ServiceChargeTransaction(int memberId, const Date& date, double charge);
    ServiceChargeTransaction(const ServiceChargeTransaction& other) = default;
    ServiceChargeTransaction(ServiceChargeTransaction&& other) noexcept = default;
    ServiceChargeTransaction& operator=(const ServiceChargeTransaction& other) = default;
    ServiceChargeTransaction& operator=(ServiceChargeTransaction&& other) noexcept = default;
    void Execute() override;

private:
    int itsMemberId;
    Date itsDate;
    double itsCharge;
};
