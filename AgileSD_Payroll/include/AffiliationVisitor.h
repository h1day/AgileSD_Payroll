#pragma once

class UnionAffiliation;
class NoAffiliation;

class AffiliationVisitor
{
public:
    AffiliationVisitor() = default;
    AffiliationVisitor(const AffiliationVisitor& other) = default;
    AffiliationVisitor(AffiliationVisitor&& other) noexcept = default;
    AffiliationVisitor& operator=(const AffiliationVisitor& other) = default;
    AffiliationVisitor& operator=(AffiliationVisitor&& other) noexcept = default;
    virtual ~AffiliationVisitor() = default;

    virtual void visit(NoAffiliation& af) = 0;
    virtual void visit(UnionAffiliation& af) = 0;
};
