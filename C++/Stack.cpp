#include "Stack.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

template <class T>
bool Stack<T>::find(T const& elem) const {
   bool return_value = false;
   if(elems.empty()){
      throw std::out_of_range("Stack<>find(T const& elem): empty stack");
   }

   typename std::vector<T>::const_iterator result;
   result = find_if (elems.begin(), elems.end(), [elem] (T const found_elem) { return (elem == found_elem);});

   if (result != elems.end()){
      std::cout << "The first element match is: " << *result << std::endl;
      return_value = true;
   }
   return return_value;
}

template <class T>
void Stack<T>::push (T const& elem) { 
   // append copy of passed element 
   elems.push_back(elem);
} 

template <class T>
void Stack<T>::pop () { 
   if (elems.empty()) { 
      throw std::out_of_range("Stack<>::pop(): empty stack"); 
   }
   
   // remove last element 
   elems.pop_back();
} 

template <class T>
T Stack<T>::top () const { 
   if (elems.empty()) { 
      throw std::out_of_range("Stack<>::top(): empty stack"); 
   }
   
   // return copy of last element 
   return elems.back();
}

