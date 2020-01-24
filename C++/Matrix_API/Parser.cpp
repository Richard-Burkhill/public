#include "Parser.hpp"

#include <sstream>
#include <iostream>

void Parser::parse_var_or_num (std::string line)
{
    std::cout << "parse_var_or_num" << std::endl;
    while (isspace(line[index]))
    {
        index++;
    }
    if (isalnum(line[index]) || line[index] == '.')
    {
        if(isalpha(line[index]))
        {
            while(isalpha(line[index]))
            {
                //found varaible
                variable += line[index++];
            }
        }
        else
        {
            parse_num(line);
        }
    }
    std::cout << variable << std::endl;
}

void Parser::parse_operator (std::string line)
{
    std::cout << "parse_operator" << std::endl;
    while (isspace(line[index++]))
    {
    }
    if (line[index] == '=')
    {
        //Found an equals operator
    }
    else if (line[index] == '*')
    {
        //Found a multiply operator
    }
    else if (line[index] = '~')
    {
        //Found a Transpose operator, check this is the correct symbol
    }
}

void Parser::parse_num (std::string line)
{
    std::cout << "parse_num" << std::endl;
    while ((!isalpha(line[index]) && isalnum(line[index])) || line[index] == '.')
    {
        //found number or matrix
        number += line[index++];
    }
    if (is_comma_or_space_then_another_number(line) || is_semi_colon_then_another_number(line))
    {
        define_matrix (number, line, column);
    }
}

bool Parser::is_comma_or_space_then_another_number (std::string line)
{
    std::cout << "is_comma_or_space_then_another_number" << std::endl;
    bool return_value = false;
    int temp_index = index;
    
    while (isspace(line[temp_index]) || (line[temp_index] == ','))
    {
        temp_index++;
        std::cout << "Found space or comma" << std::endl;
    }
    if (isalnum(line[temp_index]) && !isalpha(line[temp_index]) && (temp_index > index))
    {
        return_value = true;
        index = temp_index;
        std::cout << "A number" << std::endl;
    }
    else{
        std::cout << line[temp_index] << std::endl;
        std::cout << "Not a number" << std::endl;
    }
    return return_value;
}

bool Parser::is_semi_colon_then_another_number (std::string line)
{
    std::cout << "is_semi_colon_then_another_number" << std::endl;
    bool return_value = false;
    int temp_index = index;
    
    while (isspace(line[temp_index]) || (line[temp_index] == ';'))
    {
        temp_index++;
    }
    if (isalnum(line[temp_index]) && !isalpha(line[temp_index]) && (temp_index > index))
    {
        return_value = true;
        index = temp_index;
        while (isspace(line[index])){
            index++;
        }
        std::cout << "Next char after semi colon " << line[index] << std::endl;
        for (std::string::iterator str_itr = line.begin()+index; str_itr != line.end(); ++str_itr){
            std::cout << *str_itr;
        }
        std::cout << std::endl;
    }
    return return_value;
}

void Parser::define_matrix(std::string number, std::string line, std::vector<double>& column)
{
    std::cout << "defining matrix" << std::endl;
    std::stringstream str_to_num;
    str_to_num << number;
    double new_number;   
    str_to_num >> new_number;
    column.push_back(new_number);
    std::cout << "Pushed back " << new_number << std::endl;
    number.clear();

    while ((!isalpha(line[index]) && isalnum(line[index])) || line[index] == '.')
    {
        //found number or matrix
        number += line[index++];
    }
    if (is_comma_or_space_then_another_number(line))
    {
        define_matrix (number, line, column);
    }
    else if (is_semi_colon_then_another_number(line))
    {
        while ((!isalpha(line[index]) && isalnum(line[index])) || line[index] == '.')
        {
            //found number or matrix
            number += line[index++];
        }

        str_to_num << number;
        double new_number;   
        str_to_num >> new_number;
        column.push_back(new_number);
        std::cout << "Pushed back " << new_number << std::endl;

        rows.push_back(column);
        column.clear();
        number.clear();

        define_matrix (number, line, column);
//        for (auto col : rows){
//            std::cout << "Next column" << std::endl;
//            for (double num : col){
//                std::cout << num << std::endl;
//            }
//        }
    }
}

