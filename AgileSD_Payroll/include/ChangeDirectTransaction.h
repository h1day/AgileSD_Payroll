#ifndef CHANGEDIRECTTRANSACTION_H
#define CHANGEDIRECTTRANSACTION_H

#include "ChangeMethodTransaction.h"
#include <string>
using namespace std;

class ChangeDirectTransaction : public ChangeMethodTransaction
{
 public:
    ~ChangeDirectTransaction() override;
  ChangeDirectTransaction(int empId, string bank, string account);
    PaymentMethod* GetMethod() const override;
 private:
  string itsBank;
  string itsAccount;
};
#endif
