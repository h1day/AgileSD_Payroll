#ifndef CHANGEMETHODTRANSACTION_H
#define CHANGEMETHODTRANSACTION_H
#include "ChangeEmployeeTransaction.h"

class PaymentMethod;

class ChangeMethodTransaction : public ChangeEmployeeTransaction
{
 public:
    ~ChangeMethodTransaction() override;
  ChangeMethodTransaction(int empId);

  virtual PaymentMethod* GetMethod() const = 0;
    void Change(Employee&) override;
};

#endif
