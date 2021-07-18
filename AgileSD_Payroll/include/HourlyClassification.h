#ifndef HOURLYCLASSIFICATION_H
#define HOURLYCLASSIFICATION_H

#include <map>

#include "PaymentClassification.h"
#include "Date.h"

class TimeCard;

class HourlyClassification : public PaymentClassification
{
 public:
    ~HourlyClassification() override;
  HourlyClassification(double hourlyRate);
  double GetRate() const {return itsRate;}

  void AddTimeCard(TimeCard* tc);
  TimeCard* GetTimeCard(const Date& date);

    double CalculatePay(PayCheck&) const override;

 private:
  double CalculatePayForTimeCard(TimeCard*) const;
  double itsRate;
  std::map<Date, TimeCard*> itsTimeCards;

};

#endif
