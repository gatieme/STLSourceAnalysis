#include <iostream>
#include <algorithm>

#include <iomanip>
#include <cstdlib>

#include <stack>
#include <list>

using namespace std;


int main( )
{
    stack< int, list<int> > istack;

    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout <<"size = " <<istack.size( ) <<", ";
    cout <<"top = "<<istack.top( ) <<endl;

    istack.pop( );
    cout <<"size = " <<istack.size( ) <<", ";
    cout <<"top = "<<istack.top( ) <<endl;

    istack.pop( );
    cout <<"size = " <<istack.size( ) <<", ";
    cout <<"top = "<<istack.top( ) <<endl;

    istack.pop( );
    cout <<"size = " <<istack.size( ) <<", ";
    cout <<"top = "<<istack.top( ) <<endl;

    return 0;
}
