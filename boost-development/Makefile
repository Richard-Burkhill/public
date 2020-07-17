TARGET_EXEC ?= test_tcp_server

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

LDFLAGS := -lm -ldl -lpthread -L/usr/lib/x86_64-linux-gnu/ -lboost_filesystem

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

LIB_OBJS := bespoke_connection.o tcp_client.o tcp_connection.o tcp_server.o
TEST_SERVER_OBJS := $(LIB_OBJS) tcp_server_main.o
TEST_CLIENT_OBJS := tcp_client_main.o tcp_client.o

LIB_SRC := boost-tcp/bespoke_connection.cpp boost_tcp_client/tcp_client.cpp boost-tcp/tcp_connection.cpp boost-tcp/tcp_server.cpp
TEST_SERVER_SRC := $(LIB_SRC) boost-tcp/tcp_server_main.cpp
TEST_CLIENT_SRC := boost_tcp_client/tcp_client_main.cpp boost_tcp_client/tcp_client.cpp

all:
	make tcp_server_lib
	make test_tcp_server
	make test_tcp_client

tcp_server_lib:
	$(CXX) -c $(LIB_SRC)
	ar rvs tcp_server.a bespoke_connection.o tcp_client.o tcp_connection.o tcp_server.o

test_tcp_server: $(TEST_SERVER_SRC)
	$(CXX) $(TEST_SERVER_SRC) -o $@ $(LDFLAGS)

test_tcp_client: $(TEST_CLIENT_SRC)
	$(CXX) $(TEST_CLIENT_SRC) -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	$(RM) *.o
	$(RM) *.a
	$(RM) test_tcp_client
	$(RM) test_tcp_server

-include $(DEPS)

MKDIR_P ?= mkdir -p


