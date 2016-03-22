#include <iostream>
#include <cstring>

///  Ä£°æÌØ»¯

template <class T>
int compare(const T &left, const T&right)
{
    std::cout <<"in template<class T>..." <<std::endl;
    return (left - right);
}


template < >
int compare<const char*>(const char* &left, const char* &right)
{
    std::cout <<"in special template< >..." <<std::endl;

    return strcmp(left, right);
}

int main( )
{
    compare(1, 4);

    const char *left = "gatieme";
    const char *right = "jeancheng";
    compare(left, right);
    return 0;
}
