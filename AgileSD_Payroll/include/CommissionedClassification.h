#pragma once
#include <map>

#include "PaymentClassification.h"
#include "Date.h"
class SalesReceipt;

class CommissionedClassification : public PaymentClassification
{
public:
    ~CommissionedClassification() override;
    CommissionedClassification(double salary, double commissionRate);
    CommissionedClassification(const CommissionedClassification& other) = default;
    CommissionedClassification(CommissionedClassification&& other) noexcept = default;
    CommissionedClassification& operator=(const CommissionedClassification& other) = default;
    CommissionedClassification& operator=(CommissionedClassification&& other) noexcept = default;

    double GetSalary() const;
    double GetRate() const;

    SalesReceipt* GetReceipt(const Date& saleDate);
    void AddReceipt(SalesReceipt*);

    double CalculatePay(PayCheck&) const override;

private:
    double itsSalary;
    double itsCommissionRate;
    std::map<Date, SalesReceipt*> itsReceipts;
};
