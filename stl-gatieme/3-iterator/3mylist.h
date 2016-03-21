#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>

template <typename T>
class ListItem
{
public :
    T value( ) const
    {
        return this->m_value;
    }

    ListItem *next( ) const
    {
        return this->m_next;
    }
protected:
    T           m_value;
    ListItem    *m_next;
};


using namespace std;

template <typename T>
class list
{
public :
    void insert_front(T value);

    void insert_end(T value);

    void display(std::ostream &os std:;cout) const;

protected :

    ListItem<T> *m_end;
    ListItem<T> *m_front;
    long        m_size;
};




