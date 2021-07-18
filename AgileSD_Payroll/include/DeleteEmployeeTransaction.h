#pragma once
#include "Transaction.h"

class DeleteEmployeeTransaction : public Transaction
{
public:
    ~DeleteEmployeeTransaction() override;
    explicit DeleteEmployeeTransaction(int empId);
    void Execute() override;
private:
    int itsEmpId;
};
