#pragma once
#include "ChangeMethodTransaction.h"
#include <string>


class ChangeMailTransaction : public ChangeMethodTransaction
{
public:
    ~ChangeMailTransaction() override;
    ChangeMailTransaction(int empId, std::string address);
    ChangeMailTransaction(const ChangeMailTransaction& other) = default;
    ChangeMailTransaction(ChangeMailTransaction&& other) noexcept = default;
    ChangeMailTransaction& operator=(const ChangeMailTransaction& other) = default;
    ChangeMailTransaction& operator=(ChangeMailTransaction&& other) noexcept = default;
    PaymentMethod* GetMethod() const override;
private:
    std::string itsAddress;
};
