#include <memory>
#include <iostream>
using namespace std;

class A
{
public:
    A( )
    {
        id = ++count;
        cout <<"create A" <<id  <<std::endl;
    }

    ~A()
    {
        cout <<"destroy A" <<id <<std::endl;
    }

private:
    static int count;
    int id;
};

int A::count = 0;

/*  调用该函数会丢失掉所有权 */
void sink(auto_ptr<A> a)
{
    cout << "Enter sink()\n";
}

/*  调用该函数会创建对象，并获取所有权  */
auto_ptr<A> create()
{
    cout << "Enter create()\n";
    auto_ptr<A> a(new A());
    return a;
}

int main(int argc, char *argv[])
{
    //auto_ptr<string> pstr(new string("abcd"));
    //auto_ptr<string> pstr = new string("abcd");
    auto_ptr<A> a1 = create();
    cout << "Exit create()\n";


    auto_ptr<A> a2 = a1;            /* 赋值操作会转移所有权，此时a1无效了*/

    auto_ptr<A> a3(new A());


    sink(a2);                       /* 传参会丢失所有权，会发现a2的释放在sink函数中进行*/

    cout << "Exit sink()\n";
    return 0;
}
