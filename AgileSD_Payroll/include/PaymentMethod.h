#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H

class PayCheck;

class PaymentMethod
{
 public:
  virtual ~PaymentMethod();

  virtual void Pay(PayCheck&) = 0;
};
#endif
