sudo apt install python-mysqldb
sudo apt install libmysqlcppconn-dev
sudo apt install libmysqlclient-dev
sudo apt install mysql-client
sudo apt install mysql-server
sudo mysql_secure_installation
sudo mysql -u root -p
CREATE USER 'tester'@'localhost' IDENTIFIED BY 'MyPassword';
GRANT ALL PRIVILEGES ON * . * TO 'tester'@'localhost';
FLUSH PRIVILEGES;
CREATE DATABASE MyDatabase;
