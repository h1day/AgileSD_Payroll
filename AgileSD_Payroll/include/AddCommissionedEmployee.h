#ifndef ADDCOMMISSIONEDEMPLOYEE_H
#define ADDCOMMISSIONEDEMPLOYEE_H

#include "AddEmployeeTransaction.h"

class AddCommissionedEmployee : public AddEmployeeTransaction
{
 public:
    ~AddCommissionedEmployee() override;
  AddCommissionedEmployee(int empId, string name, string address, double salary, double commissionRate);
  PaymentClassification* GetClassification() const override;
  PaymentSchedule* GetSchedule() const override;

 private:
  double itsSalary;
  double itsCommissionRate;
};
#endif
