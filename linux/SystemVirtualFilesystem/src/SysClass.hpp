#ifndef SYS_VIRTUAL_CLASS_H
#define SYS_VIRTUAL_CLASS_H

#include <string>
using namespace std;
/* GPIO Class
 * Purpose: Each object instantiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */
class SysClass
{
public:
    SysClass();  // create a GPIO object that controls GPIO4 (default
    SysClass(string x); // create a GPIO object that controls GPIOx, where x is passed to this constructor
    int export_gpio(); // exports GPIO
    int unexport_gpio(); // unexport GPIO
    int setdir_gpio(string dir); // Set GPIO Direction
    int setval_gpio(string val); // Set GPIO Value (putput pins)
    int getval_gpio(string& val); // Get GPIO Value (input/ output pins)
    string get_gpionum(); // return the GPIO number associated with the instance of an object
    unsigned int get_sys_temperature(void);
    double get_battery_charge_full_design(void);
    double get_battery_charge_full(void);
    double get_battery_charge_now(void);
    double get_battery_current_now(void);
    unsigned char get_battery_status(void);

private:
   string gpionum; // GPIO number associated with the instance of an object
   string export_gpio_str;
   string unexport_gpio_str;
   string system_temperature;
   string battery_charge_full_design;
   string battery_charge_full;
   string battery_charge_now;
   string battery_current_now;
   string battery_status;
};

#endif
