#include "simple_jjalloc.h"  

#include<vector>  
#include<iostream>  

using namespace std;  

	
int main()  
{  
    {  
        int ia[5]={0,1,2,3,4};  
        unsigned int i;  
      
        vector<int,JJ::mallocator<int> > iv(ia,ia+5);//使用了JJ::mallocator的alloc来分配内存   
        for(int i=0;i<iv.size();i++)  
        {  
            cout<<iv[i]<<"\t";  
        }  
        cout<<endl;  
        //为什么没有用JJ::mallocator的destroy来回收内存，而自动用了vector的析构函数来回收 ？？？？明明指定了空间配置器是JJ::mallocator了啊  
    }  
      
    return 0;  
}   