//静态常量整数初始化
#include <iostream>
using namespace std;

template <typename T>
class testClass
{

public:

    static const int _datai = 5;
    static const long _datal = 3L;
    static const char _datac = 'c';
};

int main()
{
    cout<<testClass<int>::_datai<<endl;
    cout<<testClass<long>::_datal<<endl;
    cout<<testClass<char>::_datac<<endl;

    return 0;
}
