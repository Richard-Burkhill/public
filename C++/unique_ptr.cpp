#include<iostream>
#include<string>
#include<memory>
#include<iomanip>

using namespace std;

class Dog {
   void Bark(){cout<< "I want to be the boss";}
   virtual void complain () = 0;
};

class British_BUlldog : public Dog {
   void complain () {cout << "I waddle when I walk, I don't like it so much" << endl;}
};

class French_Pickanees : public Dog {
   void complain () {cout << "I will pick your knees if my devotee gives you too much attention";}
};

std::unique_ptr<Dog> k911;

int main(){

   unique_ptr<Dog> ubbd = std::make_unique<British_BUlldog>();
   unique_ptr<Dog> ufpn = std::make_unique<French_Pickanees>();

}
