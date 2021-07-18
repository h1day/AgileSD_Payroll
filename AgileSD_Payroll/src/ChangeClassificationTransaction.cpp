#include "ChangeClassificationTransaction.h"

ChangeClassificationTransaction::~ChangeClassificationTransaction() = default;

ChangeClassificationTransaction::ChangeClassificationTransaction(int empId)
    : ChangeEmployeeTransaction(empId)
{
}

void ChangeClassificationTransaction::Change(Employee& e)
{
    e.SetClassification(GetClassification());
    e.SetSchedule(GetSchedule());
}
