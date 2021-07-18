#pragma once
#include "Transaction.h"
#include <string>

class PaymentClassification;
class PaymentSchedule;

class AddEmployeeTransaction : public Transaction
{
public:
    ~AddEmployeeTransaction() override;
    AddEmployeeTransaction(int empId, std::string name, std::string address);
    AddEmployeeTransaction(const AddEmployeeTransaction& other) = default;
    AddEmployeeTransaction(AddEmployeeTransaction&& other) noexcept = default;
    AddEmployeeTransaction& operator=(const AddEmployeeTransaction& other) = default;
    AddEmployeeTransaction& operator=(AddEmployeeTransaction&& other) noexcept = default;
    virtual PaymentClassification* GetClassification() const = 0;
    virtual PaymentSchedule* GetSchedule() const = 0;
    void Execute() override;

private:
    int itsEmpId;
    std::string itsName;
    std::string itsAddress;
};
