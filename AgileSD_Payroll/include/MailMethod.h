#ifndef MAILMETHOD_H
#define MAILMETHOD_H

#include "PaymentMethod.h"
#include <string>

class MailMethod : public PaymentMethod
{
 public:
  virtual ~MailMethod();
  explicit MailMethod(std::string address);
  std::string GetAddress() const {return itsAddress;}

  virtual void Pay(PayCheck&);

 private:
    std::string itsAddress;
};

#endif
