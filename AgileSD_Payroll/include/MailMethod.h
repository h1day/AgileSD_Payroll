#pragma once
#include "PaymentMethod.h"
#include <string>

class MailMethod : public PaymentMethod
{
public:
    ~MailMethod() override;
    explicit MailMethod(std::string address);
    std::string GetAddress() const { return itsAddress; }

    void Pay(PayCheck&) override;

private:
    std::string itsAddress;
};
