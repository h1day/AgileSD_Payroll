#pragma once
#include "ChangeEmployeeTransaction.h"

class PaymentClassification;
class PaymentSchedule;

class ChangeClassificationTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeClassificationTransaction() override;
    explicit ChangeClassificationTransaction(int empId);
    ChangeClassificationTransaction(const ChangeClassificationTransaction& other) = default;
    ChangeClassificationTransaction(ChangeClassificationTransaction&& other) noexcept = default;
    ChangeClassificationTransaction& operator=(const ChangeClassificationTransaction& other) = default;
    ChangeClassificationTransaction& operator=(ChangeClassificationTransaction&& other) noexcept = default;
    void Change(Employee&) override;
    virtual PaymentClassification* GetClassification() const = 0;
    virtual PaymentSchedule* GetSchedule() const = 0;
};
