#pragma once
#include "AffiliationVisitor.h"

class AffiliationEraser : public AffiliationVisitor
{
public:
    void visit(NoAffiliation& a) override;
    void visit(UnionAffiliation& a) override;
    void visit(StudyAffiliation& a) override;
};
