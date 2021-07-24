#include "TimeCardTransaction.h"

#include <stdexcept>
#include <utility>
#include "Employee.h"
#include "PayrollDatabase.h"
#include "HourlyClassification.h"
#include "TimeCard.h"
#include "Date.h"

extern PayrollDatabase g_payrollDatabase;

TimeCardTransaction::~TimeCardTransaction() = default;

TimeCardTransaction::TimeCardTransaction(Date date, double hours, int empId)
    : itsEmpId(empId)
      , itsDate(std::move(date))
      , itsHours(hours)
{
}

void TimeCardTransaction::Execute()
{
    Employee* e = g_payrollDatabase.GetEmployee(itsEmpId);
    if (e)
    {
        PaymentClassification* pc = e->GetClassification();
        if (auto hc = dynamic_cast<HourlyClassification*>(pc))
        {
            hc->AddTimeCard(new TimeCard(itsDate, itsHours));
        }
        else
            throw std::runtime_error("Tried to add TimeCard to non-hourly employee");
    }
    else
        throw std::runtime_error("No such employee.");
}
