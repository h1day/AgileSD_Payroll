#ifndef DIRECTMETHOD_H
#define DIRECTMETHOD_H

#include "PaymentMethod.h"
#include <string>

class DirectMethod : public PaymentMethod
{
 public:
    ~DirectMethod() override;
	DirectMethod(std::string bank, std::string account);
	std::string GetBank() {return itsBank;}
	std::string GetAccount() {return itsAccount;}

    void Pay(PayCheck&) override;

 private:
	std::string itsBank;
	std::string itsAccount;
};
#endif
