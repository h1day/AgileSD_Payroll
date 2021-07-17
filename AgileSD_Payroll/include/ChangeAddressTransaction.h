#ifndef CHANGEADDRESSTRANSACTION_H
#define CHANGEADDRESSTRANSACTION_H

#include "ChangeEmployeeTransaction.h"
#include <string>
using namespace std;

class ChangeAddressTransaction : public ChangeEmployeeTransaction
{
 public:
  virtual ~ChangeAddressTransaction();
  ChangeAddressTransaction(int empid, string address);
  virtual void Change(Employee& e);

 private:
  string itsAddress;
};

#endif
