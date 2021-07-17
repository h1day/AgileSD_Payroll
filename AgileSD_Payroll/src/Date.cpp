#include "Date.h"

long Date::secondsPerDay = 60L * 60L * 24L;

Date::Date()
{
  time_t now = time(NULL);
  //itsTimeStruct = *(localtime(&now));
  const errno_t err = localtime_s(&itsTimeStruct, &now);
  if (err) {
      throw;
  }
  itsTimeStruct.tm_sec = 0;
  itsTimeStruct.tm_min = 0;
  itsTimeStruct.tm_hour = 12;
  itsTime = mktime(&itsTimeStruct);
}

Date::Date(int month, int day, int year)
{
  memset(reinterpret_cast<char*>(&itsTimeStruct), 0, sizeof(itsTimeStruct));
  itsTimeStruct.tm_mon = month-1;
  itsTimeStruct.tm_mday = day;
  itsTimeStruct.tm_year = year-1900;
  itsTimeStruct.tm_sec = 0;
  itsTimeStruct.tm_min = 0;
  itsTimeStruct.tm_hour = 12;
  itsTime = mktime(&itsTimeStruct);
  const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
  if(err) {
      throw;
  }
}

Date::Date(const Date& theDate)
{	
  *this = theDate;	
}

Date::~Date() {}

Date& Date::operator= (const Date& theDate)
{
  itsTime = theDate.itsTime;
  const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
  if (err) {
      throw;
  }
  return *this;
}

int Date::GetMonth() const {return itsTimeStruct.tm_mon + 1;}
int Date::GetDay() const   {return itsTimeStruct.tm_mday;}
int Date::GetYear() const  {return itsTimeStruct.tm_year+1900;}

Date::DayOfWeek Date::GetDayOfWeek() const
{
  return static_cast<DayOfWeek>(itsTimeStruct.tm_wday);
}

std::string Date::GetDayOfWeekName() const
{
  std::string retval;
  switch(GetDayOfWeek())
    {
    case DayOfWeek::sunday:
      retval = "Sunday";
      break;
    case DayOfWeek::monday:
      retval = "Monday";
      break;
    case DayOfWeek::tuesday:
      retval = "Tuesday";
      break;
    case DayOfWeek::wednesday:
      retval = "Wednesday";
      break;
    case DayOfWeek::thursday:
      retval = "Thursday";
      break;
    case DayOfWeek::friday:
      retval = "Friday";
      break;
    case DayOfWeek::saturday:
      retval = "Saturday";
      break;
    }
  return retval;
}

std::ostream& operator<< (std::ostream& o, const Date& theDate)
{
  o << theDate.GetMonth() << '/'
    << theDate.GetDay() << '/'
    << theDate.GetYear();
  return o;
}

std::istream& operator>> (std::istream& i, Date& theDate)
{
  int month, day, year;
  char slash;
  i >> month >> slash >> day >> slash >> year;
  Date tmp(month, day, year);
  theDate = tmp;
  return i;
}

int Date::operator== (const Date& theDate) const
{
  return itsTime == theDate.itsTime;
}

int Date::operator!= (const Date& theDate) const
{
  return itsTime != theDate.itsTime;
}

int Date::operator< (const Date& theDate) const
{
  return itsTime < theDate.itsTime;
}

int Date::operator> (const Date& theDate) const
{
  return itsTime > theDate.itsTime;
}

int Date::operator<= (const Date& theDate) const
{
  return itsTime <= theDate.itsTime;
}

int Date::operator>= (const Date& theDate) const
{
  return itsTime >= theDate.itsTime;
}

Date operator+ (int days, const Date& theDate)
{
  Date retval = theDate;
  retval += days;
  return retval;
}

Date operator+ (const Date& theDate, int days)
{
  return days + theDate;
}

Date Date::operator- (int days) const
{
  Date retval = *this;
  retval -= days;
  return retval;
}

int Date::operator- (const Date& theDate) const
{
  return static_cast<int>((itsTime - theDate.itsTime) / static_cast<time_t>(secondsPerDay));
}

Date& Date::operator+= (int days)
{
  itsTime += static_cast<time_t>(days) * secondsPerDay;
  const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
  if (err) {
      throw;
  }
  return *this;
}

Date& Date::operator-= (int days)
{
  itsTime -= static_cast<time_t>(days) * secondsPerDay;
  const errno_t err = localtime_s(&itsTimeStruct, &itsTime);
  if (err) {
      throw;
  }
  return *this;
}

Date& Date::operator++ ()
{
  return ((*this) += 1);
}

Date Date::operator++ (int)  // postfix
{
  Date retval = *this;
  (*this) += 1;
  return retval;
}

Date& Date::operator-- ()
{
  return ((*this) -= 1);
}

Date Date::operator-- (int)  // postfix
{
  Date retval = *this;
  (*this) -= 1;
  return retval;
}
