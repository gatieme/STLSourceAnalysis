#include <cstdlib>
#include <iostream>


using namespace std;


int fcmp(const void *elem1, const void *elem2);


int main( )
{
    int ia[] = {32, 92, 67, 58, 10, 4, 25, 52, 59, 54};

    for(int i = 0; i < 10; i++)
    {
        cout <<ia[i] <<" ";
    }
    cout <<endl;

    qsort(ia, sizeof(ia)/sizeof(ia[0]), sizeof(ia[0]), fcmp);


    for(int i = 0; i < 10; i++)
    {
        cout <<ia[i] <<" ";
    }
    cout <<endl;

}

int fcmp(const void *elem1, const void *elem2)
{
    const int *i1 = (const int *)elem1;
    const int *i2 = (const int *)elem2;

    return (*i1 - *i2);
}
