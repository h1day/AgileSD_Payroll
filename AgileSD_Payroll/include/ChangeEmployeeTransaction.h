#pragma once
#include "Transaction.h"
#include "Employee.h"

class ChangeEmployeeTransaction : public Transaction
{
public:
    explicit ChangeEmployeeTransaction(int empId);
    ~ChangeEmployeeTransaction() override;
    void Execute() override;
    virtual void Change(Employee&) = 0;

protected:
    int GetEmpId() const { return itsEmpId; }

private:
    int itsEmpId;
};
