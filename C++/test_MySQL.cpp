#include "MySQL.hpp"


int main()
{
   MySQL sql_class = MySQL("tester", "GreenFellowRoad3550#!", "MyDatabase");
   sql_class.query("SELECT * FROM address_book");
}
