#pragma once
#include "Affiliation.h"

class ServiceCharge;

class StudyAffiliation : public Affiliation
{
public:
    ~StudyAffiliation() override;
    StudyAffiliation(int memberId, double dues);
    StudyAffiliation(const StudyAffiliation& other) = default;
    StudyAffiliation(StudyAffiliation&& other) noexcept = default;
    StudyAffiliation& operator=(const StudyAffiliation& other) = default;
    StudyAffiliation& operator=(StudyAffiliation&& other) noexcept = default;

    double GetDues() const { return itsDues + plus; }
    int GetMemberId() const { return itsMemberId; }
    double CalculateDeductions(PayCheck&) const override;
    void Accept(AffiliationVisitor& v) override;

private:
    static constexpr double  plus{100.0};
    int itsMemberId;
    double itsDues;
};
