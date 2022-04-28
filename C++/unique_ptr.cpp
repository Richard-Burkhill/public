#include<iostream>
#include<string>
#include<memory>
#include<iomanip>

using namespace std;

class Dog {
public:
   void Bark(){cout<< "I want to be the boss"<< endl;}
   virtual void complain () = 0;
};

class British_Bulldog : public Dog {
public:
   void complain () {cout << "I waddle when I walk, I don't like it so much" << endl;}
};

class French_Pickanees : public Dog {
public:
   void complain () {cout << "I will pick your knees if my devotee gives you too much attention"<<endl;}
};

int main(){

   unique_ptr<British_Bulldog> ubbd = std::make_unique<British_Bulldog>();
   unique_ptr<French_Pickanees> ufpn = std::make_unique<French_Pickanees>();
   
   ubbd->complain();
   ufpn->complain();
   
   std::unique_ptr<Dog> k911;
   
   k911 = std::move(ufpn);
   k911->complain();
}
