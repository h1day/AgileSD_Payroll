#include "SalesReceiptTransaction.h"

#include <utility>
#include "Employee.h"
#include "PayrollDatabase.h"
#include "CommissionedClassification.h"
#include "SalesReceipt.h"

extern PayrollDatabase g_payrollDatabase;

SalesReceiptTransaction::~SalesReceiptTransaction() = default;
SalesReceiptTransaction::SalesReceiptTransaction(Date saleDate, double amount, int empId)
    : itsEmpId(empId)
      , itsSaleDate(std::move(saleDate))
      , itsAmount(amount)
{
}

void SalesReceiptTransaction::Execute()
{
    Employee* e = g_payrollDatabase.GetEmployee(itsEmpId);
    if (e)
    {
        PaymentClassification* pc = e->GetClassification();
        if (auto cc = dynamic_cast<CommissionedClassification*>(pc))
        {
            cc->AddReceipt(new SalesReceipt(itsSaleDate, itsAmount));
        }
        else
            throw std::runtime_error("Tried to add sales receipt to non-commissioned employee");
    }
    else
        throw std::runtime_error("No such employee.");
}
