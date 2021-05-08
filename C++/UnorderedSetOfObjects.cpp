// UnorderedSetOfObjects.cpp

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Point
{
  int x;
  int y;

  Point() { }
  Point(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
  
  bool operator==(const Point& otherPoint) const
  {
    if (this->x == otherPoint.x && this->y == otherPoint.y) return true;
    else return false;
  }

  struct HashFunction
  {
    size_t operator()(const Point& point) const
    {
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};

class Student
{
  int mId;
  std::string mName;
public:
  Student(int id, std::string name) :
      mId(id), mName(name)
  {
  }
  void
  displayInfo()
  {
    std::cout << mId << " :: " << mName << std::endl;
  }
  bool
  operator ==(const Student & obj) const
  {
    if (mId == obj.mId)
      return true;
    else
      return false;
  }
  int
  getId() const
  {
    return mId;
  }
  std::string
  getName() const
  {
    return mName;
  }
};

// class for hash function
class MyHashFunction {
public:
    // id is returned as hash function
    size_t operator()(const Student& t) const
    {
        return t.getId();
    }
};

int main(int argc, char** argv)
{
   unordered_set<Student, MyHashFunction> setOfStudents;
}
