#ifndef PAYMENTCLASSIFICATION_H
#define PAYMENTCLASSIFICATION_H

class PayCheck;

class PaymentClassification
{
 public:
  virtual ~PaymentClassification();

  virtual double CalculatePay(PayCheck&) const = 0;

};
#endif
