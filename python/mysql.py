import MySQLdb

try:
	connection = MySQLdb.connect (host = "localhost", user = "tester",
                                 passwd = "GreenFellowRoad3550#!", db = "MyDatabase")
except MySQLdb.Error as e:
	print("Error %d: %s" % (e.args[0], e.args[1]))
	sys.exit(1)

cursor = connection.cursor()

sql_command = """
CREATE TABLE address_book ( 
row_number INTEGER PRIMARY KEY,
last_name VARCHAR(30), 
first_name VARCHAR(20), 
telephone_number VARCHAR(15),
email_address VARCHAR(50));"""

cursor.execute(sql_command)

sql_command = """INSERT INTO address_book (row_number, last_name, first_name, telephone_number, email_address)
    VALUES (1, "Blogs", "Joan", "441999987654", "blogs-joan@fake-email-address.uk");"""
cursor.execute(sql_command)

sql_command = """INSERT INTO address_book (row_number, last_name, first_name, telephone_number, email_address)
    VALUES (2, "Blogs", "Joe", "441999987654", "blogs-joe@fake-email-address.uk");"""
cursor.execute(sql_command)

sql_command = """INSERT INTO address_book (row_number, last_name, first_name, telephone_number, email_address)
    VALUES (3, "Doe", "John", "441998987654", "john-doe@fake-email-address.uk");"""
cursor.execute(sql_command)

# never forget this, if you want the changes to be saved:
connection.commit()

connection.close()
