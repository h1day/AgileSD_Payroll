#include "CommissionedClassification.h"
#include "SalesReceipt.h"
#include "PayCheck.h"

CommissionedClassification::~CommissionedClassification(){
    for (auto& element : itsReceipts)
    {
        delete element.second;
    }
    itsReceipts.clear();
}

CommissionedClassification::CommissionedClassification(double salary, double commissionRate)
    : itsSalary(salary)
      , itsCommissionRate(commissionRate)
{
}

double CommissionedClassification::GetSalary() const
{
    return itsSalary;
}

double CommissionedClassification::GetRate() const
{
    return itsCommissionRate;
}

SalesReceipt* CommissionedClassification::GetReceipt(const Date& saleDate)
{
    return itsReceipts[saleDate];
}

void CommissionedClassification::AddReceipt(SalesReceipt* receipt)
{
    itsReceipts[receipt->GetSaleDate()] = receipt;
}

double CommissionedClassification::CalculatePay(PayCheck& pc) const
{
    double commission = 0.0;
    for (auto i = itsReceipts.begin(); i != itsReceipts.end(); ++i)
    {
        SalesReceipt* receipt = (*i).second;
        if (Date::IsBetween(receipt->GetSaleDate(), pc.GetPayPeriodStartDate(), pc.GetPayPeriodEndDate()))
        {
            commission += receipt->GetAmount() * itsCommissionRate;
        }
    }
    return itsSalary + commission;
}
