#ifndef TIME_CONV_CLASS_H
#define TIME_CONV_CLASS_H

#include <cstddef>

class TimeConvert
{
public:
   TimeConvert();
   void from_hours (double dbl_hours);
   void from_minutes (double dbl_minutes);

   void print (void);
private: 
   unsigned int hours;
   unsigned short minutes;
   unsigned short seconds;
   double decimal_seconds;
};

#endif
