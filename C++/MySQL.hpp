/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include "mysql_driver.h" 

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class MySQL {
   public:
      MySQL() = delete;
      MySQL(const MySQL&) = default;
      MySQL(MySQL&&) = default;
      MySQL& operator=(const MySQL&) = default;
      MySQL& operator=(MySQL&&) = default;

      MySQL(std::string user, std::string password, std::string database);

      void query(std::string the_query);

   protected:
      sql::mysql::MySQL_Driver *driver;
      sql::Connection *con;
      sql::Statement *stmt;
      sql::ResultSet *res;
};

