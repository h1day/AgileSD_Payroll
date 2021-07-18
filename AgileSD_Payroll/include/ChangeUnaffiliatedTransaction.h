#ifndef CHANGEUNAFFILIATEDTRANSACTION_H
#define CHANGEUNAFFILIATEDTRANSACTION_H

#include "ChangeAffiliationTransaction.h"

class ChangeUnaffiliatedTransaction : public ChangeAffiliationTransaction
{
 public:
    ~ChangeUnaffiliatedTransaction() override;
  ChangeUnaffiliatedTransaction(int empId);
    Affiliation* GetAffiliation() const override;
    void RecordMembership(Employee*) override;
};
#endif
