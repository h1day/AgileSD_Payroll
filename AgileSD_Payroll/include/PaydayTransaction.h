#ifndef PAYDAYTRANSACTION_H
#define PAYDAYTRANSACTION_H

#include "Transaction.h"
#include "Date.h"

#include <map>

class PayCheck;

class PaydayTransaction : public Transaction
{
 public:
  virtual ~PaydayTransaction();
  PaydayTransaction(Date payDate);
  virtual void Execute();
  PayCheck* GetPaycheck(int empId);
  int GetPaycheckCount() const;

 private:
  Date itsPayDate;
  std::map<int, PayCheck*> itsPaychecks;
};

#endif
