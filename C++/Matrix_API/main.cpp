#include <iostream>

#include "Parser.hpp"

using namespace std;

#define line_length 256

int main (int argc, char** argv){
    char line[line_length];

    std::cin.getline (line,line_length);
    Parser matrx_parser;

    matrx_parser.parse_var_or_num (line);
    matrx_parser.parse_operator (line);

}
