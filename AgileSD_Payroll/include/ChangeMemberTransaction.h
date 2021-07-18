#ifndef CHANGEMEMBERTRANSACTION_H
#define CHANGEMEMBERTRANSACTION_H

#include "ChangeAffiliationTransaction.h"

class ChangeMemberTransaction : public ChangeAffiliationTransaction
{
 public:
    ~ChangeMemberTransaction() override;
  ChangeMemberTransaction(int empId, int memberId, double dues);
    Affiliation* GetAffiliation() const override;
    void RecordMembership(Employee*) override;
 private:
  int itsMemberId;
  double itsDues;
};
#endif
