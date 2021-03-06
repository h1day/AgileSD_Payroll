#include "PayCheck.h"

#include <utility>

PayCheck::PayCheck(Date payPeriodStartDate,
                   Date payPeriodEndDate)
    : itsPayPeriodStartDate(std::move(payPeriodStartDate))
      , itsPayPeriodEndDate(std::move(payPeriodEndDate))
{
    itsGrossPay = 0;
    itsNetPay = 0;
    itsDeductions = 0;
}

void PayCheck::SetGrossPay(double grossPay)
{
    itsGrossPay = grossPay;
}

void PayCheck::SetNetPay(double netPay)
{
    itsNetPay = netPay;
}

void PayCheck::SetDeductions(double deductions)
{
    itsDeductions = deductions;
}

void PayCheck::SetField(const std::string& name, std::string value)
{
    itsFields[name] = std::move(value);
}

std::string PayCheck::GetField(const std::string& name)
{
    return itsFields[name];
}
