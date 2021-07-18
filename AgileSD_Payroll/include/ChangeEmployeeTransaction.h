#pragma once
#include "Transaction.h"
#include "Employee.h"

class ChangeEmployeeTransaction : public Transaction
{
public:
    explicit ChangeEmployeeTransaction(int empId);
    ~ChangeEmployeeTransaction() override;
    ChangeEmployeeTransaction(const ChangeEmployeeTransaction& other) = default;
    ChangeEmployeeTransaction(ChangeEmployeeTransaction&& other) noexcept = default;
    ChangeEmployeeTransaction& operator=(const ChangeEmployeeTransaction& other) = default;
    ChangeEmployeeTransaction& operator=(ChangeEmployeeTransaction&& other) noexcept = default;
    void Execute() override;
    virtual void Change(Employee&) = 0;

protected:
    int GetEmpId() const { return itsEmpId; }

private:
    int itsEmpId;
};
