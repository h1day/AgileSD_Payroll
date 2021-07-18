#include "ChangeAffiliationTransaction.h"

ChangeAffiliationTransaction::~ChangeAffiliationTransaction() = default;

ChangeAffiliationTransaction::ChangeAffiliationTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
}

void ChangeAffiliationTransaction::Change(Employee& e)
{
    RecordMembership(&e);
    e.SetAffiliation(GetAffiliation());
}
