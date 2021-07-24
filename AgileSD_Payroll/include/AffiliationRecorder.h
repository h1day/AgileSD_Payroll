#pragma once
#include "AffiliationVisitor.h"

class Employee;

class AffiliationRecorder : public AffiliationVisitor
{
public:
    explicit AffiliationRecorder(Employee& e);

    void visit(NoAffiliation& a) override;
    void visit(UnionAffiliation& a) override;
private:
    Employee* itsEmployee;
};
