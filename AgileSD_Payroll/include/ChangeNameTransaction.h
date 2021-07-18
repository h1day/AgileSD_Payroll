#ifndef CHANGE_NAME_TRANSACTION_H
#define CHANGE_NAME_TRANSACTION_H

#include "ChangeEmployeeTransaction.h"
#include <string>

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
public:
    ~ChangeNameTransaction() override;
    ChangeNameTransaction(int empId, std::string name);
    void Change(Employee&) override;

private:
    std::string itsName;
};

#endif
