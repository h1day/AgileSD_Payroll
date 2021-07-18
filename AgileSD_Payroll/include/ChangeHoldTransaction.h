#ifndef CHANGEHOLDTRANSACTION_H
#define CHANGEHOLDTRANSACTION_H

#include "ChangeMethodTransaction.h"

class ChangeHoldTransaction : public ChangeMethodTransaction
{
 public:
    ~ChangeHoldTransaction() override;
    explicit ChangeHoldTransaction(int empId);
    PaymentMethod* GetMethod() const override;
};
#endif
