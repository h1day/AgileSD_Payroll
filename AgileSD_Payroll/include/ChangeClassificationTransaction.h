#pragma once
#include "ChangeEmployeeTransaction.h"

class PaymentClassification;
class PaymentSchedule;

class ChangeClassificationTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeClassificationTransaction() override;
    explicit ChangeClassificationTransaction(int empId);
    void Change(Employee&) override;
    virtual PaymentClassification* GetClassification() const = 0;
    virtual PaymentSchedule* GetSchedule() const = 0;
};
