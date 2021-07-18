#pragma once
#include "Transaction.h"
#include "Date.h"

class TimeCardTransaction : public Transaction
{
public:
    ~TimeCardTransaction() override;
    TimeCardTransaction(Date date, double hours, int empId);
    TimeCardTransaction(const TimeCardTransaction& other) = default;
    TimeCardTransaction(TimeCardTransaction&& other) noexcept = default;
    TimeCardTransaction& operator=(const TimeCardTransaction& other) = default;
    TimeCardTransaction& operator=(TimeCardTransaction&& other) noexcept = default;

    void Execute() override;

private:
    int itsEmpId;
    Date itsDate;
    double itsHours;
};
