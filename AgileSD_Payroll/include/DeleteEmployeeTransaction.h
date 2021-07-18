#ifndef DELETEEMPLOYEETRANSACTION_H
#define DELETEEMPLOYEETRANSACTION_H

#include "Transaction.h"

class DeleteEmployeeTransaction : public Transaction
{
 public:
    ~DeleteEmployeeTransaction() override;
  DeleteEmployeeTransaction(int empId);
    void Execute() override;
 private:
  int itsEmpid;
};
#endif
