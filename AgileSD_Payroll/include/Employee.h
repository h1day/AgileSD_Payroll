#pragma once
#include <string>

class PaymentSchedule;
class PaymentClassification;
class PaymentMethod;
class Affiliation;
class PayCheck;
class Date;

class Employee
{
public:
    virtual ~Employee();
    Employee(int empId, std::string name, std::string address);
    Employee(const Employee& other) = default;
    Employee(Employee&& other) noexcept = default;
    Employee& operator=(const Employee& other) = default;
    Employee& operator=(Employee&& other) noexcept = default;

    void SetName(std::string name);
    void SetAddress(std::string address);
    void SetClassification(PaymentClassification*);
    void SetMethod(PaymentMethod*);
    void SetSchedule(PaymentSchedule*);
    void SetAffiliation(Affiliation*);

    int GetEmpId() const { return itsEmpId; }
    std::string GetName() const { return itsName; }
    std::string GetAddress() const { return itsAddress; }
    PaymentMethod* GetMethod() const { return itsPaymentMethod; }
    PaymentClassification* GetClassification() const { return itsClassification; }
    PaymentSchedule* GetSchedule() const { return itsSchedule; }
    Affiliation* GetAffiliation() const { return itsAffiliation; }

    void Payday(PayCheck&) const;
    bool IsPayDate(const Date& payDate) const;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const;

private:
    int itsEmpId;
    std::string itsName;
    std::string itsAddress;
    PaymentClassification* itsClassification;
    PaymentSchedule* itsSchedule;
    PaymentMethod* itsPaymentMethod;
    Affiliation* itsAffiliation;
};
