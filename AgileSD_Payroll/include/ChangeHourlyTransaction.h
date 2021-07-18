#ifndef CHANGEHOURLYTRANSACTION_H
#define CHANGEHOURLYTRANSACTION_H

#include "ChangeClassificationTransaction.h"

class ChangeHourlyTransaction : public ChangeClassificationTransaction
{
 public:
    ~ChangeHourlyTransaction() override;
  ChangeHourlyTransaction(int empId, double hourlyRate);
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

 private:
  double itsHourlyRate;
};

#endif
