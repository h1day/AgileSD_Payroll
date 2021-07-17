#ifndef MAILMETHOD_H
#define MAILMETHOD_H

#include "PaymentMethod.h"
#include <string>
using namespace std;

class MailMethod : public PaymentMethod
{
 public:
  virtual ~MailMethod();
  MailMethod(string address);
  string GetAddress() const {return itsAddress;}

  virtual void Pay(Paycheck&);

 private:
  string itsAddress;
};

#endif
