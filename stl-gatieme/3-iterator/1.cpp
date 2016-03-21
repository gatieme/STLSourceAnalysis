// expre_bad_typeid.cpp
// compile with: /EHsc /GR
#include <typeinfo.h>
#include <iostream>

class A{
public:
  // object for class needs vtable
  // for RTTI
  virtual ~A();
};

using namespace std;
int main() {
A* a = NULL;

try {
  cout << typeid(*a).name() << endl; // Error condition
  }
catch (bad_typeid){
  cout << "Object is NULL" << endl;
  }
}