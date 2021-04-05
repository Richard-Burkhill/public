#!/bin/bash

exe_name=$(echo "$1" | cut -f 1 -d '.')
echo "The exe name will be $exe_name"

all_args=$@

obj=${all_args#"$1"}
obj=$(echo "${obj##*( )}")
echo "List of objects is $obj"

#might need
#g++ -MMD -MP -std=gnu++17 -g -lm -ldl -lpthread -c $obj -o $exe_name
#for more than one object
g++ -MMD -MP -std=gnu++17 -g -lm -ldl -lpthread $obj -o $exe_name

chmod +x $exe_name
