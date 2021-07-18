#include "TimeCardTransaction.h"
#include "Employee.h"
#include "PayrollDatabase.h"
#include "HourlyClassification.h"
#include "TimeCard.h"
#include "Date.h"

extern PayrollDatabase g_payrollDatabase;

TimeCardTransaction::~TimeCardTransaction() = default;

TimeCardTransaction::TimeCardTransaction(const Date& date, double hours, int empId)
  : itsEmpId(empId)
  , itsDate(date)
  , itsHours(hours)
{
}

void TimeCardTransaction::Execute()
{
  Employee* e = g_payrollDatabase.GetEmployee(itsEmpId);
  if (e){
    PaymentClassification* pc = e->GetClassification();
    if (auto hc = dynamic_cast<HourlyClassification*>(pc)) {
      hc->AddTimeCard(new TimeCard(itsDate, itsHours));
    } else
      throw("Tried to add TimeCard to non-hourly employee");
  } else
    throw("No such employee.");
}
