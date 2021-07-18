#include "Employee.h"

#include <utility>
#include "NoAffiliation.h"
#include "PaymentClassification.h"
#include "PaymentSchedule.h"
#include "PaymentMethod.h"
#include "PayCheck.h"

Employee::~Employee()
{
    delete itsClassification;
    delete itsSchedule;
    delete itsPaymentMethod;
}

Employee::Employee(int empId, std::string name, std::string address)
    : itsEmpId(empId)
      , itsName(std::move(name))
      , itsAddress(std::move(address))
      , itsClassification(nullptr)
      , itsSchedule(nullptr)
      , itsPaymentMethod(nullptr)
      , itsAffiliation(new NoAffiliation())
{
}

void Employee::SetName(std::string name)
{
    itsName = std::move(name);
}

void Employee::SetAddress(std::string address)
{
    itsAddress = std::move(address);
}

void Employee::SetClassification(PaymentClassification* pc)
{
    delete itsClassification;
    itsClassification = pc;
}

void Employee::SetSchedule(PaymentSchedule* ps)
{
    delete itsSchedule;
    itsSchedule = ps;
}

void Employee::SetMethod(PaymentMethod* pm)
{
    delete itsPaymentMethod;
    itsPaymentMethod = pm;
}

void Employee::SetAffiliation(Affiliation* af)
{
    delete itsAffiliation;
    itsAffiliation = af;
}

bool Employee::IsPayDate(const Date& payDate) const
{
    return itsSchedule->IsPayDate(payDate);
}

Date Employee::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return itsSchedule->GetPayPeriodStartDate(payPeriodEndDate);
}

void Employee::Payday(PayCheck& pc) const
{
    const double grossPay = itsClassification->CalculatePay(pc);
    const double deductions = itsAffiliation->CalculateDeductions(pc);
    const double netPay = grossPay - deductions;
    pc.SetGrossPay(grossPay);
    pc.SetDeductions(deductions);
    pc.SetNetPay(netPay);
    itsPaymentMethod->Pay(pc);
}
