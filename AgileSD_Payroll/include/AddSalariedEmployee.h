#ifndef ADDSALARIEDEMPLOYEE_H
#define ADDSALARIEDEMPLOYEE_H

#include "AddEmployeeTransaction.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
 public:
    ~AddSalariedEmployee() override;
  AddSalariedEmployee(int empId, string name, string address, double salary);
  PaymentClassification* GetClassification() const override;
  PaymentSchedule* GetSchedule() const override;

 private:
  double itsSalary;
};
#endif
