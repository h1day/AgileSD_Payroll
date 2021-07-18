#ifndef ADDHOURLYEMPLOYEE_H
#define ADDHOURLYEMPLOYEE_H

#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
 public:
    ~AddHourlyEmployee() override;
    AddHourlyEmployee(int empId, string name, string address, double hourlyRate);
    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

 private:
  double itsHourlyRate;
};
#endif
