#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>


using namespace std;

int main()
{
    const int arraySize = 7;
    int ia[arraySize] = {0, 1, 2, 3, 4, 5, 6};

    vector<int> ivect(ia, ia + arraySize);
    list<int> ilist(ia, ia + arraySize);
    deque<int> ideque(ia, ia + arraySize);

    vector<int>::iterator it1 = find(ivect.begin(), ivect.end(), 4);
    if(it1 == ivect.end())
    {
       cout <<"4 not found..." <<endl;
    }
    else
    {
        cout <<"find 4 @ " <<*it1 <<endl;
    }


    list<int>::iterator it2 = find(ilist.begin(), ilist.end(), 4);
    if(it2 == ilist.end())
    {
       cout <<"4 not found..." <<endl;
    }
    else
    {
        cout <<"find 4 @ " <<*it1 <<endl;
    }

    deque<int>::iterator it3 = find(ideque.begin(), ideque.end(), 4);
    if(it3 == ideque.end())
    {
       cout <<"4 not found..." <<endl;
    }
    else
    {
        cout <<"find 4 @ " <<*it1 <<endl;
    }

    return 0;
}
