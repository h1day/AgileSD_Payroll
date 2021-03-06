#pragma once
#include "Date.h"
#include <map>
#include <string>

class PayCheck
{
public:
    virtual ~PayCheck() = default;
    PayCheck(Date payPeriodStart, Date payPeriodEnd);
    PayCheck(const PayCheck& other) = default;
    PayCheck(PayCheck&& other) noexcept = default;
    PayCheck& operator=(const PayCheck& other) = default;
    PayCheck& operator=(PayCheck&& other) noexcept = default;

    void SetGrossPay(double grossPay);
    void SetDeductions(double deductions);
    void SetNetPay(double netPay);

    double GetGrossPay() const { return itsGrossPay; }
    double GetDeductions() const { return itsDeductions; }
    double GetNetPay() const { return itsNetPay; }

    Date GetPayPeriodEndDate() const { return itsPayPeriodEndDate; }
    Date GetPayPeriodStartDate() const { return itsPayPeriodStartDate; }
    void SetField(const std::string& name, std::string value);
    std::string GetField(const std::string& name);

private:
    Date itsPayPeriodStartDate;
    Date itsPayPeriodEndDate;
    double itsGrossPay{0};
    double itsNetPay{0};
    double itsDeductions{0};
    std::map<std::string, std::string> itsFields;
};
