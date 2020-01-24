#include "MySQL.hpp"

MySQL::MySQL(std::string user, std::string password, std::string database)
{
   /* Create a connection */
   try {     
     driver = sql::mysql::get_driver_instance();
   }
   catch (std::exception std_exp)
   {
     std::cout << "Caught std exception" << std::endl;
   }
   catch (...)
   {
     std::cout << "Caught system exception" << std::endl;
   }

   con = driver->connect("tcp://127.0.0.1:3306", user, password);

   /* Connect to the MySQL test database */
   con->setSchema(database);
}

void MySQL::query(std::string the_query)
{
   stmt = con->createStatement();
   res = stmt->executeQuery(the_query);
}

