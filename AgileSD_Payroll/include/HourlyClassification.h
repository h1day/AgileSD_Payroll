#pragma once
#include <map>
#include "PaymentClassification.h"
#include "Date.h"

class TimeCard;

class HourlyClassification : public PaymentClassification
{
public:
    ~HourlyClassification() override;
    explicit HourlyClassification(double hourlyRate);

    HourlyClassification(const HourlyClassification& other) = default;
    HourlyClassification(HourlyClassification&& other) noexcept = default;
    HourlyClassification& operator=(const HourlyClassification& other) = default;
    HourlyClassification& operator=(HourlyClassification&& other) noexcept = default;
    double GetRate() const { return itsRate; }

    void AddTimeCard(TimeCard* tc);
    TimeCard* GetTimeCard(const Date& date);

    double CalculatePay(PayCheck&) const override;

private:
    double CalculatePayForTimeCard(TimeCard*) const;
    double itsRate;
    std::map<Date, TimeCard*> itsTimeCards;
};
