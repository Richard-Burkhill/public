MySQL:
	g++ -c MySQL.cpp -lmysqlcppconn-static -lmysqlclient
clean:
	rm -f *.o
	rm -f test_MySQL

test_MySQL:
	g++ -c test_MySQL.cpp
	g++ MySQL.o test_MySQL.o -o $@ -lmysqlcppconn-static -lmysqlclient

game_sim:
	g++ -std=gnu++17 -g all_pins.hpp all_pins.cpp pin.hpp pin.cpp move.hpp move.cpp main_game_sim.cpp -o game_sim

all:
	make clean
	make MySQL
	make test_MySQL
	make game_sim



