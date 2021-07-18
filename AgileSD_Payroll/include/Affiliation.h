#pragma once
class PayCheck;

class Affiliation
{
public:
    virtual ~Affiliation();
    Affiliation();

    virtual double CalculateDeductions(PayCheck&) const = 0;
};
