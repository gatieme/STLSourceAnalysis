///c++11 条款1：理解模板类型推导
///http://blog.csdn.net/coolmeme/article/details/43986163
///http://blog.csdn.net/shinehoo/article/details/5722362
///  STL源码剖析 PDF-119/534

#include <iostream>

template <typename T>
class C             //  这个泛化版本允许接受T为任意类型
{
    // NOP...
};


template <typename T>
class C<T*>             //  这个泛化版本j仅适用于"T为原生指针的情况"
{
    //  T为原生指针便是T为任何型别的一个更进一步的条件限制
    // NOP...
};


template <typename Iter>
struct iterator_traits
{
    typedef typename I::value_type value_type；
};


template <class Iter>
//typename Iter::value_type          ///  这一整行func的返回值类型
typename iterator_traits<Iter>::value_type
func(Iter iter)
{
    ///
    return *iter;
}


template<class Iter>
struct iterator_traits<Iter*>
{
    typedef T value_type;
};


int main(void)
{
    MyIter<int> ite(new int(8));
    std::cout <<func(ite) <<std::endl;
    return 0;
}
