
#ifndef CHANGEEMPLOYEETRANSACTION_H
#define CHANGEEMPLOYEETRANSACTION_H

#include "Transaction.h"
#include "Employee.h"
 
class ChangeEmployeeTransaction : public Transaction
{
 public:
  ChangeEmployeeTransaction(int empId);
  ~ChangeEmployeeTransaction() override;
  void Execute() override;
  virtual void Change(Employee&) = 0;
  
 protected:
  int GetEmpId() {return itsEmpId;}

 private:
  int itsEmpId;
};

#endif
