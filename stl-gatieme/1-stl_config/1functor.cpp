//STL采用仿函数排序
#include <iostream>
using namespace std;


//  由于将operator()重载了, 因此plus成了一个仿函数
template <class T>
struct myplus
{
    T operator()(const T& x, const T& y) const
    {
        return x + y;
    }
};

//  由于将operator()重载了, 因此minus成了一个仿函数

template <class T>
struct myminus
{
    T operator()(const T& x, const T& y) const
    {
        return x - y;
    }
};

int main()
{
    //  创建仿函数对象
    myplus<int> plusobj;
    myminus<int> minusobj;

    cout<<plusobj(3,5)<<endl;
    cout<<minusobj(3,5)<<endl;

    cout<<myplus<int>()(43,50)<<endl;
    cout<<myminus<int>()(43,50)<<endl;

    return 1;
}
