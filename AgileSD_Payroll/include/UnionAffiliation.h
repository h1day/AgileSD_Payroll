#pragma once
#include "Affiliation.h"
#include "Date.h"
#include <map>

class ServiceCharge;

class UnionAffiliation : public Affiliation
{
public:
    ~UnionAffiliation() override;
    UnionAffiliation(int memberId, double dues);
    UnionAffiliation(const UnionAffiliation& other) = default;
    UnionAffiliation(UnionAffiliation&& other) noexcept = default;
    UnionAffiliation& operator=(const UnionAffiliation& other) = default;
    UnionAffiliation& operator=(UnionAffiliation&& other) noexcept = default;

    void AddServiceCharge(const Date& date, double amount);
    ServiceCharge* GetServiceCharge(const Date& date);
    double GetDues() const { return itsDues; }
    int GetMemberId() const { return itsMemberId; }
    double CalculateDeductions(PayCheck&) const override;
    void Accept(AffiliationVisitor& v) override;

private:
    int itsMemberId;
    double itsDues;
    std::map<Date, ServiceCharge*> itsServiceCharges;
};
