#ifndef CHANGE_NAME_TRANSACTION_H
#define CHANGE_NAME_TRANSACTION_H

#include "ChangeEmployeeTransaction.h"
#include <string>

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeNameTransaction() override;
    ChangeNameTransaction(int empId, std::string name);
    ChangeNameTransaction(const ChangeNameTransaction& other) = default;
    ChangeNameTransaction(ChangeNameTransaction&& other) noexcept = default;
    ChangeNameTransaction& operator=(const ChangeNameTransaction& other) = default;
    ChangeNameTransaction& operator=(ChangeNameTransaction&& other) noexcept = default;
    void Change(Employee&) override;

private:
    std::string itsName;
};

#endif
