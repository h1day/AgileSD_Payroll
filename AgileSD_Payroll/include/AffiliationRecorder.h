#pragma once
#include "AffiliationVisitor.h"

class Employee;

class AffiliationRecorder : public AffiliationVisitor
{
public:
    explicit AffiliationRecorder(Employee& e);

    void visit(NoAffiliation& a) override;
    void visit(UnionAffiliation& a) override;
    void visit(StudyAffiliation& a) override;
private:
    Employee* itsEmployee;
};
