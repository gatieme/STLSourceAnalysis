//≤‚ ‘class template÷–”µ”–static data members.  
#include <iostream>  
using namespace std;  
  
template <typename T>  
class testclass  
{  
public:  
  static int _data;  
};  
  
template<> int testclass<int>::_data = 1;  
template<> int testclass<char>::_data = 2;  
  
int main()  
{  
  cout<<testclass<int>::_data<<endl;  
  cout<<testclass<char>::_data<<endl;  
  
  testclass<int> obji1, obji2;  
  testclass<char> objc1, objc2;  
  
  cout<<obji1._data<<endl;  
  cout<<obji2._data<<endl;  
  cout<<objc1._data<<endl;  
  cout<<objc2._data<<endl;  
  
  obji1._data = 3;  
  objc2._data = 4;  
    
  cout<<obji1._data<<endl;  
  cout<<obji2._data<<endl;  
  cout<<objc1._data<<endl;  
  cout<<objc2._data<<endl;  
  
  return 1;  
}  