#ifndef AFFILIATION_H
#define AFFILIATION_H

class PayCheck;

class Affiliation
{
 public:
  virtual ~Affiliation();
  Affiliation();

  virtual double CalculateDeductions(PayCheck&) const = 0;
};

#endif
