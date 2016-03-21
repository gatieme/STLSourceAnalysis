//测试class template 指针和const参数支持  
#include <iostream>  
using namespace std;  
  
template <class I, class O>  
struct testClass  
{  
  testClass()  
  {  
    cout<<"I, O"<<endl;  
  }  
};  
  
template <class T>  
struct testClass<T*, T*>  
{  
  testClass()  
  {  
    cout<<"T*,T*"<<endl;  
  }  
};  
  
template <class T>  
struct testClass<const T*, T*>  
{  
  testClass()  
  {  
    cout<<"const T*, T*"<<endl;  
  }  
};  
  
int main()  
{  
  testClass<int, char> obj1;  
  testClass<int*, int*> obj2;  
  testClass<const int*, int*> obj3;  
  return 1;  
}  