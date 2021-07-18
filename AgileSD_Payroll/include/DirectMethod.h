#pragma once
#include "PaymentMethod.h"
#include <string>

class DirectMethod : public PaymentMethod
{
public:
    ~DirectMethod() override;
    DirectMethod(std::string bank, std::string account);
    DirectMethod(const DirectMethod& other) = default;
    DirectMethod(DirectMethod&& other) noexcept = default;
    DirectMethod& operator=(const DirectMethod& other) = default;
    DirectMethod& operator=(DirectMethod&& other) noexcept = default;

    std::string GetBank() const { return itsBank; }
    std::string GetAccount() const { return itsAccount; }

    void Pay(PayCheck&) override;

private:
    std::string itsBank;
    std::string itsAccount;
};
