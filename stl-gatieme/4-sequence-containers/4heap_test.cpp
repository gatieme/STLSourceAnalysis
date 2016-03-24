#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>


using namespace std;
void Print(int a)
{
    cout <<std::setw(4) <<a;

}

int main( )
{
    /// test heap (µ×²ãÒÔvectorÍê³É)
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    vector<int> ivec(ia, ia + 9);

    make_heap(ivec.begin( ), ivec.end( ));
    for(vector<int>::iterator iter = ivec.begin( );
        iter != ivec.end( );
        iter++)
    {
        cout <<setw(4)<<*iter;
    }
    cout <<endl;

    ivec.push_back(7);
    push_heap(ivec.begin( ), ivec.end());
    cout <<ivec.back( ) <<endl;
    ivec.pop_back( );
    for(vector<int>::iterator iter = ivec.begin( );
        iter != ivec.end( );
        iter++)
    {
        cout <<setw(4)<<*iter;
    }
    cout <<endl;

    pop_head(ivec.begin( ), ivec.end( )));
    cout <<ivec.back( ) <<endl;
    ivec.pop_back( );

    sort_head(ivec.begin(), ivect.end( ));
    for(vector<int>::iterator iter = ivec.begin( );
        iter != ivec.end( );
        iter++)
    {
        cout <<setw(4)<<*iter;
    }
    cout <<endl;

    return 0;
}

