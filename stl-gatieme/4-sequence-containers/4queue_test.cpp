#include <iostream>
#include <algorithm>

#include <iomanip>
#include <cstdlib>

#include <queue>
#include <list>

using namespace std;


int main( )
{
    queue< int, list<int> > iqueue;

    iqueue.push(1);
    iqueue.push(3);
    iqueue.push(5);
    iqueue.push(7);

    cout <<"size = " <<iqueue.size( ) <<", ";
    cout <<"top = "<<iqueue.front( ) <<endl;

    iqueue.pop( );
    cout <<"size = " <<iqueue.size( ) <<", ";
    cout <<"top = "<<iqueue.front( ) <<endl;

    iqueue.pop( );
    cout <<"size = " <<iqueue.size( ) <<", ";
    cout <<"top = "<<iqueue.front( ) <<endl;

    iqueue.pop( );
    cout <<"size = " <<iqueue.size( ) <<", ";
    cout <<"top = "<<iqueue.front( ) <<endl;

    return 0;
}
