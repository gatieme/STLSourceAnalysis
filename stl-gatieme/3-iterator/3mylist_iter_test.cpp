/*************************************************************************
    > File Name: 3mylist-iter-test.cpp
    > Author: gatieme
    > Created Time: 2016年03月21日 星期一 15时13分39秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

#include "3mylist.h"
#include "3mylist_iter.h"


int main( )
{
    List<int>   mylist;

    for(int i = 0; i < 5; i++)
    {
        mylist.insert_front(i);
        mylist.insert_end(i + 2);
    }

    mylist.display( );

    ListIter< ListItem<int> > begin(mylist.front);

    ListIter< Listitem<int> > end;                    // default 0, null
    ListIter< Listitem<int> > iter;                   // default 0, null

    iter = find(begin, end, 3);
    if(iter == end)
    {
        cout <<"not found" <<endl;
    }
    else
    {
        cout <<"found." <<iter->m_value() <<endl;
    }

    iter = find(begin, end, 7);
    if(iter == end)
    {
        cout <<"not found" <<endl;
    }
    else
    {
        cout <<"found." <<iter->m_value() <<endl;

    return 0;
}
