#pragma once
#include "Transaction.h"
#include "Date.h"
#include <map>

class PayCheck;

class PaydayTransaction : public Transaction
{
public:
    ~PaydayTransaction() override;
    explicit PaydayTransaction(Date payDate);
    PaydayTransaction(const PaydayTransaction& other) = default;
    PaydayTransaction(PaydayTransaction&& other) noexcept = default;
    PaydayTransaction& operator=(const PaydayTransaction& other) = default;
    PaydayTransaction& operator=(PaydayTransaction&& other) noexcept = default;

    void Execute() override;
    PayCheck* GetPaycheck(int empId);
    int GetPaycheckCount() const;

private:
    Date itsPayDate;
    std::map<int, PayCheck*> itsPaychecks;
};
