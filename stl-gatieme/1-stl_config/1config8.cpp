//测试class template 之内可否再有template (members)  
#include <iostream>  
using namespace std;  
  
class alloc  
{  
};  
  
template <class T, class Alloc = alloc>  
class vector  
{  
public:  
  typedef T value_type;  
  typedef value_type* iterator;  
  
  template <class I>  
  void insert(iterator position, I first, I last)  
  {  
    cout<<"insert()"<<endl;  
  }  
};  
  
int main()  
{  
  int ia[5] = {0,1,2,3,4};  
    
  cout<<*ia<<endl;  
  cout<<*(ia+4)<<endl;  
    
  vector<int> x;  
  vector<int>::iterator ite = NULL;  
  x.insert(ite, ia, ia+4);  
  return 1;  
}  