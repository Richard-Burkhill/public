#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "SysClass.hpp"

using namespace std;

SysClass::SysClass()
   : export_gpio_str("/sys/class/gpio/export"),
   unexport_gpio_str("/sys/class/gpio/unexport"),
   system_temperature("/sys/class/thermal/thermal_zone0/temp"),
   battery_charge_full_design("/sys/class/power_supply/BAT0/charge_full_design"),
   battery_charge_full("/sys/class/power_supply/BAT0/charge_full"),
   battery_charge_now("/sys/class/power_supply/BAT0/charge_now"),
   battery_current_now("/sys/class/power_supply/BAT0/current_now"),
   battery_status("/sys/class/power_supply/BAT0/status")
{
    this->gpionum = "4"; //GPIO4 is default
}

SysClass::SysClass(string gnum)
   : export_gpio_str("/sys/class/gpio/export"),
   unexport_gpio_str("/sys/class/gpio/unexport"),
   system_temperature("/sys/class/thermal/thermal_zone0/temp"),
   battery_charge_full("/sys/class/power_supply/BAT0/charge_full"),
   battery_charge_now("/sys/class/power_supply/BAT0/charge_now"),
   battery_current_now("/sys/class/power_supply/BAT0/current_now")
{
    this->gpionum = gnum;  //Instatiate SysClass object for GPIO pin number "gnum"
}

int SysClass::export_gpio()
{
    ofstream exportgpio(export_gpio_str.c_str()); // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
    if (!exportgpio.is_open()){
        cout << " OPERATION FAILED: Unable to export GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    exportgpio << this->gpionum ; //write GPIO number to export
    exportgpio.close(); //close export file
    return 0;
}

int SysClass::unexport_gpio()
{
    string unexport_str = "/sys/class/gpio/unexport";
    ofstream unexportgpio(unexport_str.c_str()); //Open unexport file
    if (!unexportgpio.is_open()){
        cout << " OPERATION FAILED: Unable to unexport GPIO"<< this->gpionum <<" ."<< endl;
        return -1;
    }

    unexportgpio << this->gpionum ; //write GPIO number to unexport
    unexportgpio.close(); //close unexport file
    return 0;
}

int SysClass::setdir_gpio(string dir)
{

    string setdir_str ="/sys/class/gpio/gpio" + this->gpionum + "/direction";
    ofstream setdirgpio(setdir_str.c_str()); // open direction file for gpio
    if (!setdirgpio.is_open())
    {
       cout << " OPERATION FAILED: Unable to set direction of GPIO"<< this->gpionum <<" ."<< endl;
       return -1;
    }

    setdirgpio << dir; //write direction to direction file
    setdirgpio.close(); // close direction file
    return 0;
}

int SysClass::setval_gpio(string val)
{

   string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
   ofstream setvalgpio(setval_str.c_str()); // open value file for gpio
   if (!setvalgpio.is_open())
   {
      cout << " OPERATION FAILED: Unable to set the value of GPIO"<< this->gpionum <<" ."<< endl;
      return -1;
   }

   setvalgpio << val ;//write value to value file
   setvalgpio.close();// close value file
   return 0;
}

int SysClass::getval_gpio(string& val)
{
   string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
   ifstream getvalgpio(getval_str.c_str());// open value file for gpio
   if (!getvalgpio.is_open())
   {
      cout << " OPERATION FAILED: Unable to get value of GPIO"<< this->gpionum <<" ."<< endl;
      return -1;
   }

   getvalgpio >> val ;  //read gpio value

   if(val != "0")
      val = "1";
   else
      val = "0";

    getvalgpio.close(); //close the value file
    return 0;
}

unsigned int SysClass::get_sys_temperature(void)
{
   ifstream getval_temperature(system_temperature.c_str());// open value file for gpio
   if (!getval_temperature.is_open())
   {
      cout << " OPERATION FAILED: Unable to get System Temperature" << endl;
      return -1;
   }

   unsigned int temp;
   getval_temperature >> temp;

   temp /= 1000;

   getval_temperature.close(); //close the value file
   return temp;
}

double SysClass::get_battery_charge_full_design(void)
{
   ifstream getval_charge_full_design(battery_charge_full_design.c_str());// open value file for gpio
   if (!getval_charge_full_design.is_open())
   {
      cout << " OPERATION FAILED: Unable to get System Temperature" << endl;
      return -1;
   }

   double charge_full_design;
   getval_charge_full_design >> charge_full_design;

   getval_charge_full_design.close(); //close the value file
   return charge_full_design;
}

double SysClass::get_battery_charge_full(void)
{
   ifstream getval_charge_full(battery_charge_full.c_str());// open value file for gpio
   if (!getval_charge_full.is_open())
   {
      cout << " OPERATION FAILED: Unable to get System Temperature" << endl;
      return -1;
   }

   double charge_full;
   getval_charge_full >> charge_full;

   getval_charge_full.close(); //close the value file
   return charge_full;
}

double SysClass::get_battery_charge_now(void)
{
   ifstream getval_charge_now(battery_charge_now.c_str());// open value file for gpio
   if (!getval_charge_now.is_open())
   {
      cout << " OPERATION FAILED: Unable to get System Temperature" << endl;
      return -1;
   }

   double charge_now;
   getval_charge_now >> charge_now;

   getval_charge_now.close(); //close the value file
   return charge_now;
}

double SysClass::get_battery_current_now(void)
{
   ifstream getval_current_now(battery_current_now.c_str());// open value file for gpio
   if (!getval_current_now.is_open())
   {
      cout << " OPERATION FAILED: Unable to get System Temperature" << endl;
      return -1;
   }

   double current_now;
   getval_current_now >> current_now;

   getval_current_now.close(); //close the value file
   return current_now;
}

unsigned char SysClass::get_battery_status(void)
{
   unsigned char charging = 0;
   ifstream getval_battery_status(battery_status.c_str());// open value file for gpio
   if (!getval_battery_status.is_open())
   {
      cout << " OPERATION FAILED: Unable to get System Temperature" << endl;
      return -1;
   }

   string val_battery_status;
   getval_battery_status >> val_battery_status;

   getval_battery_status.close(); //close the value file

   if(val_battery_status == "Charging")
   {
      charging = 1;
   }
   else if(val_battery_status == "Discharging")
   {
      charging = 0;
   }
   else
   {
      charging = 2;
   }

   return charging;
}

string SysClass::get_gpionum()
{
   return this->gpionum;
}
