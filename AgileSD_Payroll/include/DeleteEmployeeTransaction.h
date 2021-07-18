#pragma once
#include "Transaction.h"

class DeleteEmployeeTransaction : public Transaction
{
public:
    ~DeleteEmployeeTransaction() override;
    explicit DeleteEmployeeTransaction(int empId);
    DeleteEmployeeTransaction(const DeleteEmployeeTransaction& other) = default;
    DeleteEmployeeTransaction(DeleteEmployeeTransaction&& other) noexcept = default;
    DeleteEmployeeTransaction& operator=(const DeleteEmployeeTransaction& other) = default;
    DeleteEmployeeTransaction& operator=(DeleteEmployeeTransaction&& other) noexcept = default;

    void Execute() override;
private:
    int itsEmpId;
};
