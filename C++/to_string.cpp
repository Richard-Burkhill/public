//string to_string (int val);
//string to_string (long val);
//string to_string (long long val);
//string to_string (unsigned val);
//string to_string (unsigned long val);
//string to_string (unsigned long long val);
//string to_string (float val);
//string to_string (double val);
//string to_string (long double val);

#include <iostream>
#include <string>

int main()
{
    int var1=16;
       
    // Converting float to string
    std::string str1 = std::to_string(12.10);
 
    // Converting integer to string
    std::string str2 = std::to_string(9999);
   
    // Converting integer to string by taking a variable
    std::string str3 = std::to_string(var1);
 
    // Printing the strings
    std::cout << str1 << '\n';
    std::cout << str2 << '\n';
    std::cout << str3 << '\n';
    
    return 0;
}
