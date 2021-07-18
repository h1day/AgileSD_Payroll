#pragma once
#include "Transaction.h"
#include "Date.h"
#include <map>

class PayCheck;

class PaydayTransaction : public Transaction
{
public:
    ~PaydayTransaction() override;
    explicit PaydayTransaction(const Date& payDate);
    void Execute() override;
    PayCheck* GetPaycheck(int empId);
    int GetPaycheckCount() const;

private:
    Date itsPayDate;
    std::map<int, PayCheck*> itsPaychecks;
};
