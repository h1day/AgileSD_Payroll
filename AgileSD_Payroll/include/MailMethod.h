#pragma once
#include "PaymentMethod.h"
#include <string>

class MailMethod : public PaymentMethod
{
public:
    ~MailMethod() override;
    explicit MailMethod(std::string address);
    MailMethod(const MailMethod& other) = default;
    MailMethod(MailMethod&& other) noexcept = default;
    MailMethod& operator=(const MailMethod& other) = default;
    MailMethod& operator=(MailMethod&& other) noexcept = default;

    std::string GetAddress() const { return itsAddress; }

    void Pay(PayCheck&) override;

private:
    std::string itsAddress;
};
