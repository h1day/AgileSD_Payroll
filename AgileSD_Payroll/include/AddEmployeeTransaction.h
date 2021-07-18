#ifndef ADDEMPLOYEETRANSACTION_H
#define ADDEMPLOYEETRANSACTION_H

#include "Transaction.h"
#include <string>
using namespace std;

class PaymentClassification;
class PaymentSchedule;

class AddEmployeeTransaction : public Transaction
{
 public:
    ~AddEmployeeTransaction() override;
  AddEmployeeTransaction(int empId, string name, string address);
  virtual PaymentClassification* GetClassification() const = 0;
  virtual PaymentSchedule* GetSchedule() const = 0;
    void Execute() override;

 private:
  int itsEmpid;
  string itsName;
  string itsAddress;
};
#endif
