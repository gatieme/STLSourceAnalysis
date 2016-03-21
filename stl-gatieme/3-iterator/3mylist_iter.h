#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>

template <typename Item>    // item可以是单向链表及诶但或者双向列表节点
class ListIter
{
public :
    ///
    /// 构造函数
    ///
    ListIter(Item *p = NULL)
    :m_ptr(p)
    {
        /// NOP...
    }

    /// 不必实现copy ctor, 因为编译器提供缺省的行为已足够
    /// 不比实现operator=， 因为编译器提供的缺省行为已足够

    ///
    ///  重载指针运算符
    ///

    Item& operator*( ) const
    {
        return *m_ptr;
    }

    Item* oprrator->( ) const
    {
        return m_ptr;
    }


protected :
    item *m_ptr;                //  保持与容器之间的联系
};




