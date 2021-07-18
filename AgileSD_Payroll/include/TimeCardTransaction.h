#pragma once
#include "Transaction.h"
#include "Date.h"

class TimeCardTransaction : public Transaction
{
public:
    ~TimeCardTransaction() override;
    TimeCardTransaction(const Date& date, double hours, int empId);

    void Execute() override;

private:
    int itsEmpId;
    Date itsDate;
    double itsHours;
};
