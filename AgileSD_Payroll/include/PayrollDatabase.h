#pragma once
#include <map>
#include <list>

class Employee;

class PayrollDatabase
{
public:
    virtual ~PayrollDatabase() = default;
    PayrollDatabase() = default;
    PayrollDatabase(const PayrollDatabase& other) = delete;
    PayrollDatabase(PayrollDatabase&& other) noexcept = delete;
    PayrollDatabase& operator=(const PayrollDatabase& other) = delete;
    PayrollDatabase& operator=(PayrollDatabase&& other) noexcept = delete;

    Employee* GetEmployee(int empId);
    void AddEmployee(int empId, Employee*);
    void DeleteEmployee(int empId);
    void AddUnionMember(int memberId, Employee*);
    void AddStudyMember(int memberId, Employee*);
    Employee* GetUnionMember(int memberId);
    Employee* GetStudyMember(int memberId);
    void RemoveUnionMember(int memberId);
    void RemoveStudyMember(int memberId);
    void clear();
    void GetAllEmployeeIds(std::list<int>&);

private:
    std::map<int, Employee*> itsEmployees;
    std::map<int, int> itsUnionMembers;
    std::map<int, int> itsStudyMembers;
};

