#ifndef HOLDMETHOD_H
#define HOLDMETHOD_H

#include "PaymentMethod.h"

class HoldMethod : public PaymentMethod
{
 public:
    ~HoldMethod() override;

    void Pay(PayCheck&) override;
};
#endif
