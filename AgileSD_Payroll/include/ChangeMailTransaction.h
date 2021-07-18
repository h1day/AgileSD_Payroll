#ifndef CHANGEMAILTRANSACTION_H
#define CHANGEMAILTRANSACTION_H

#include "ChangeMethodTransaction.h"
#include <string>


class ChangeMailTransaction : public ChangeMethodTransaction
{
 public:
    ~ChangeMailTransaction() override;
  ChangeMailTransaction(int empId, std::string address);
    PaymentMethod* GetMethod() const override;
 private:
    std::string itsAddress;
};

#endif
