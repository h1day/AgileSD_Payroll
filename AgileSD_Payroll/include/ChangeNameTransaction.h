#ifndef CHANGENAMETRANSACTION_H
#define CHANGENAMETRANSACTION_H

#include "ChangeEmployeeTransaction.h"
#include <string>
using namespace std;

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
 public:
    ~ChangeNameTransaction() override;
  ChangeNameTransaction(int empId, string name);
    void Change(Employee&) override;

 private:
  string itsName;
};

#endif
