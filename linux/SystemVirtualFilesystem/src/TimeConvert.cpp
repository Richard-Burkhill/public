#include "TimeConvert.hpp"

#include <cmath>
#include <iostream>

TimeConvert::TimeConvert()
{

}

void TimeConvert::from_hours(double dbl_hours)
{
   hours = (unsigned int) (floor(dbl_hours));

   double dbl_minutes = (dbl_hours - hours) * 60.0;
   minutes = (unsigned short) (floor(dbl_minutes));

   double dbl_seconds = (dbl_minutes - minutes) * 60.0;
   seconds = (unsigned short) (floor(dbl_seconds));

   decimal_seconds = dbl_seconds -= seconds;
   print();
}

void TimeConvert::from_minutes (double dbl_minutes)
{
   minutes = (unsigned short) (floor(dbl_minutes));

   double dbl_seconds = (dbl_minutes - minutes) * 60.0;
   seconds = (unsigned short) (floor(dbl_seconds));

   decimal_seconds = dbl_seconds -= seconds;
   print();
}

void TimeConvert::print(void)
{
   std::cout << hours << " hours " << minutes << " minutes " << seconds << " seconds "
      << decimal_seconds << " decimal seconds" << std::endl;
}
