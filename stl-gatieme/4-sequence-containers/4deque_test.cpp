#include <iostream>
#include <algorithm>
#include <deque>
#include <iomanip>
#include <cstdlib>


using namespace std;
void Print(int a)
{
    cout <<std::setw(4) <<a;

}

int main( )
{
    deque<int, alloc, 32> ideq(20, 9);              //  alloc只适用于G++编译器
    cout <<"size = " <<ideq.size( );
    /// 现在构造了一个deque, 有20个int元素, 初值皆为9
    /// 缓冲区大小为32byte

    ///  为每个元素设定新值
    for(int i = 0; i < ideq.size( ); i++)
    {
        ideq[i] = i;
    }
    cout <<endl;



    return 0;
}

