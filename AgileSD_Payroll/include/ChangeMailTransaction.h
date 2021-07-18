#pragma once
#include "ChangeMethodTransaction.h"
#include <string>


class ChangeMailTransaction : public ChangeMethodTransaction
{
public:
    ~ChangeMailTransaction() override;
    ChangeMailTransaction(int empId, std::string address);
    PaymentMethod* GetMethod() const override;
private:
    std::string itsAddress;
};
