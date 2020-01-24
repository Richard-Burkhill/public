#include <vector>

template <class T>
class Stack { 
   public: 
      bool find(T const& elem) const;
      void push(T const&);
      void pop();
      T top() const;
   private: 
      std::vector<T> elems;
};
