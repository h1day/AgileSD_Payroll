#include "AddEmployeeTransaction.h"

#include <utility>
#include "HoldMethod.h"
#include "Employee.h"
#include "PayrollDatabase.h"

class PaymentMethod;
class PaymentSchedule;
class PaymentClassification;

extern PayrollDatabase g_payrollDatabase;

AddEmployeeTransaction::~AddEmployeeTransaction() = default;

AddEmployeeTransaction::AddEmployeeTransaction(int empId, std::string name, std::string address)
    : itsEmpId(empId)
      , itsName(std::move(name))
      , itsAddress(std::move(address))
{
}

void AddEmployeeTransaction::Execute()
{
    PaymentClassification* pc = GetClassification();
    PaymentSchedule* ps = GetSchedule();
    PaymentMethod* pm = new HoldMethod();
    auto e = new Employee(itsEmpId, itsName, itsAddress);
    e->SetClassification(pc);
    e->SetSchedule(ps);
    e->SetMethod(pm);
    g_payrollDatabase.AddEmployee(itsEmpId, e);
}
