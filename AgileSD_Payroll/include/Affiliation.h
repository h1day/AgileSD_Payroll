#pragma once
class PayCheck;
class Employee;

class Affiliation
{
public:
    virtual ~Affiliation() = default;
    Affiliation() = default;
    Affiliation(const Affiliation& other) = default;
    Affiliation(Affiliation&& other) noexcept = default;
    Affiliation& operator=(const Affiliation& other) = default;
    Affiliation& operator=(Affiliation&& other) noexcept = default;

    virtual double CalculateDeductions(PayCheck&) const = 0;
    virtual void EraseMembership() = 0;
    virtual void RecordMembership(Employee& e) = 0;
};
