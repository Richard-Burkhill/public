#include "SysClass.hpp"

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "TimeConvert.hpp"

int main (void)
{
   boost::shared_ptr<SysClass> ptr_sysClass (new SysClass());
   std::cout << "System temperature is: " << ptr_sysClass->get_sys_temperature() << std::endl;

   if (ptr_sysClass->get_battery_status() > 0)
   {
      double time_to_charge = (ptr_sysClass->get_battery_charge_full() - ptr_sysClass->get_battery_charge_now())
         / ptr_sysClass->get_battery_current_now();
      std::cout << "Time to charge is: " << time_to_charge << " hours " << std::endl;

      if (time_to_charge > 0)
      {
         TimeConvert time_convertor;
         time_convertor.from_hours(time_to_charge);
      }
   }
   else
   {
      double time_to_discharge = ptr_sysClass->get_battery_charge_now() / ptr_sysClass->get_battery_current_now();
      std::cout << "Time to discharge is: " << time_to_discharge << " hours " << std::endl;

      if (time_to_discharge > 0)
      {
         TimeConvert time_convertor;
         time_convertor.from_hours(time_to_discharge);
      }
   }

   double percentage_of_max_charging_capacity = 
      (ptr_sysClass->get_battery_charge_full() / ptr_sysClass->get_battery_charge_full_design()) * 100.0;

   std::cout << "Battery now has " << percentage_of_max_charging_capacity << "%" << " of designed charged capacity." << std::endl;
}
