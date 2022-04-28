#include<iostream>
#include<string>
#include<memory>
#include<iomanip>

using namespace std;

class Dog {
   void Bark(){cout<< "I want to be the boss";}
};

std::unique_ptr<Dog> k9;
std::unique_ptr<Dog> k911;

int main(){

   unique_ptr<Dog> ubbd = std::make_unique<Dog>();
   unique_ptr<Dog> ufpn = std::make_unique<Dog>();

}
