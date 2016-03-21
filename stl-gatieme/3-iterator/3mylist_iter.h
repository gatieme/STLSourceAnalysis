#ifndef  __MYLIST_ITER_H__
#define  __MYLIST_ITER_H__

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>

#include "3mylist.h"


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

    Item* operator->( ) const
    {
        return m_ptr;
    }

    ///
    ///  以下两个operator++遵循标准做法,
    ///

    //(1) pre-increment operator...
    //  it meens ++i == iter.operator++( )
    Item& operator++( )
    {
        m_ptr = m_ptr->m_next;

        return (*this);
    }

    //(2) post-increment operator...
    //  it meens i++ == iter.operator++(int)
    Item& operator++(int)
    {
        Item temp = *this;
        ++*this;                //  调用前置++运算符

        return temp;
    }

    bool operator==(const Item &i) const
    {
        return m_ptr == i.m_ptr;
    }

    bool operator!=(const Item &i) const
    {
        return m_ptr != i.m_ptr;
    }

protected :
    Item *m_ptr;                //  保持与容器之间的联系
};



#endif  // #define  __MYLIST_ITER_H__
