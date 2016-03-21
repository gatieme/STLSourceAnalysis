//≤‚ ‘class template explicit specializatin  
#include <iostream>  
using namespace std;  
  
template <class Key>  
struct hash  
{  
  void operator()()  
  {  
    cout<<"hash<T>"<<endl;  
  }  
};  
  
template<>  
struct hash<char>  
{  
  void operator()()  
  {  
    cout<<"hash<char>"<<endl;  
  }  
};  
  
template<>  
struct hash<unsigned char>  
{  
  void operator()()  
  {  
    cout<<"hash<unsinged char>"<<endl;  
  }  
};  
  
int main()  
{  
  hash<long> t1;  
  hash<char> t2;  
  hash<unsigned char> t3;  
  
  t1();  
  t2();  
  t3();  
  
  return 1;  
}  