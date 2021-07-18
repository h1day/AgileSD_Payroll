#pragma once
#include <map>
#include <list>

class Employee;

class PayrollDatabase
{
public:
    virtual ~PayrollDatabase();
    Employee* GetEmployee(int empId);
    void AddEmployee(int empId, Employee*);
    void DeleteEmployee(int empId);
    void AddUnionMember(int memberId, Employee*);
    Employee* GetUnionMember(int memberId);
    void RemoveUnionMember(int memberId);
    void clear();
    void GetAllEmployeeIds(std::list<int>&);

private:
    std::map<int, Employee*> itsEmployees;
    std::map<int, int> itsUnionMembers;
};

