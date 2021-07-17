#include "PayCheck.h"

PayCheck::~PayCheck() = default;

PayCheck::PayCheck(const Date& payPeriodStartDate,
                   const Date& payPeriodEndDate)
: itsPayPeriodStartDate(payPeriodStartDate)
, itsPayPeriodEndDate(payPeriodEndDate)
{
	itsGrossPay =  0;
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

void PayCheck::SetField(std::string name, std::string value)
{
  itsFields[name] = value;
}

std::string PayCheck::GetField(std::string name)
{
  return itsFields[name];
}
