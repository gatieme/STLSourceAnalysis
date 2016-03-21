//临时对象的产生与运用
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class print
{
public:
  void operator()(const T& elem)
  {
    cout<<elem<<' ';
  }
};

int main()
{
    int ia[6] = {0,1,2,3,4,5};
    vector<int> iv(ia, ia+6);

    for_each(iv.begin(), iv.end(), print<int>());

    cout<<endl;

  return 1;
}
