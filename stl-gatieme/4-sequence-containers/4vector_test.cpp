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
    int i;
    vector<int> iv(2, 9);

    cout <<"size = " <<iv.size() <<endl;                //  2
    cout <<"capacity = " <<iv.capacity() <<endl;        //  2

    iv.push_back(1);
    cout <<"size = " <<iv.size() <<endl;                //  3
    cout <<"capacity = " <<iv.capacity() <<endl;        //  4

    iv.push_back(2);
    cout <<"size = " <<iv.size() <<endl;                //  4
    cout <<"capacity = " <<iv.capacity() <<endl;        //  4


    iv.push_back(3);
    cout <<"size = " <<iv.size() <<endl;                //  5
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8


    iv.push_back(4);
    cout <<"size = " <<iv.size() <<endl;                //  6
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8


    for(i = 0; i < iv.size( ); i++)
    {
        cout <<std::setw(4) <<iv[i];
    }
    cout <<endl;

    iv.push_back(5);
    cout <<"size = " <<iv.size() <<endl;                //  7
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8

    for(vector<int>::iterator iter = iv.begin();
        iter != iv.end();
        iter++)
    {
        cout <<std::setw(4) <<*iter;
    }
    cout <<endl;

    iv.pop_back( );
    iv.pop_back( );
    cout <<"size = " <<iv.size() <<endl;                //  5
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8

    iv.pop_back( );
    cout <<"size = " <<iv.size() <<endl;                //  4
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8

    vector<int>::iterator ivite = find(iv.begin(), iv.end( ), 1);
    if(ivite != iv.end( ))
    {
        iv.erase(ivite);
    }
    cout <<endl;

    cout <<"size = " <<iv.size() <<endl;                //  3
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8
    for_each(iv.begin(), iv.end(), Print);
    cout <<endl;

    vector<int>::iterator ite = find(iv.begin(), iv.end( ), 2);
    if(ite != iv.end( ))
    {
        iv.insert(ite, 3, 7);
    }
    cout <<"size = " <<iv.size() <<endl;                //  3
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8
    for_each(iv.begin(), iv.end(), Print);
    cout <<endl;

    iv.clear( );
    cout <<"size = " <<iv.size() <<endl;                //  3
    cout <<"capacity = " <<iv.capacity() <<endl;        //  8


    return 0;
}

