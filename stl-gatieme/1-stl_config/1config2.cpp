
#include <iostream>
#include <vector>

using namespace std;

int main()
{
# if defined(__sgi)
 cout << "__sig" << endl;
# endif

# if defined(__GNUC__)
 cout << "_GNUC_" << endl;
 //cout << _GNUC_ << ' ' << _GNUC_MINOR_ << endl;
# endif

# ifdef __STL_NO_DRAND48
 cout << "__STL_NO_DRAND48 defined" << endl;
# else
 cout << "__STL_NO_DRAND48 undefined"  << endl;
# endif

# ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
 cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG defined" << endl;
# else
 cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG undefined"  << endl;
# endif

# ifdef __STL_WIN32THREADS
 cout << "__STL_WIN32THREADS defined" << endl;
# else
 cout << "__STL_WIN32THREADSk undefined"  << endl;
# endif

# ifdef __STL_ASSERTIONS
 cout << "__STL_ASSERTIONS defined" << endl;
# else
 cout << "__STL_ASSERTIONS undefined"  << endl;
# endif

# ifdef __STL_NEED_BOOL
 cout << "__STL_NEED_BOOL defined" << endl;
# else
 cout << "__STL_NEED_BOOL undefined"  << endl;
# endif

}
