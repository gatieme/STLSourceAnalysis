#ifndef SIMPLE_JJALLOC_H  
#define SIMPLE_JJALLOC_H  
#include<new>         //for placement new   
#include<cstddef> //for ptrdiff_t,size_t  
#include<cstdlib> //for exit()  
#include<climits> //for UINT_MAX十进制的最大值   
#include<iostream>    //for cerr  
  
namespace JJ  
{  
    /*****************ptrdiff_t与size_t类型*****size_type与difference_type类型********************  
    ****ptrdiff_t:signed类型，通常用于两指针减法操作的结果，它可以是负数。（因为指针相减有正有负）  
    ****size_t:unsigned类型，用于指明数组长度，它是非负整数。 
    ****size_type:unsigned类型，容器中元素长度或下表，vector<int>::size_type i=0; 
    ****difference_type:signed类型，表示迭代器差距，vector<int>::difference_type=iter1-iter2 
    ****前两者位于标准类库std内，后两者为stl对象所有  
    *********************************************************************************************/  
    template<class T>  
    inline T* _allocate(ptrdiff_t size, T*)  
    {     
        std::cout<<"I'm _allocate in simple_jjalloc!"<<std::endl;  
        /**************************new_handler与set_new_handler***********************************  
        ****new_handler:内存分配失败后，调用的处理函数。 
        ****set_new_handler:参数是被指定的new_handler函数指针，返回参数也是new_handler是被替换掉的new_handler  
        *****************************************************************************************/    
        std::set_new_handler(0);  
        /****************::*********************************************************************** 
        ****"::":全局作用。比如::luo这就是个全局变量，而luo这是个局部变量  
        ****"::":类作用。比如Node::function() 
        ****"::":名字空间。比如std::size_t  
        *****************************************************************************************/    
        T *tmp=(T*)(::operator new((size_t)(size*sizeof(T))));  
        if(tmp == 0)//没有前面的std::set_new_handler(0);把内存分配失败后的异常调用函数给替换掉，就执行不到这儿   
        {  
            std::cout<<"failed!"<<std::endl;  
            std::cerr<<"out of memory"<<std::endl;  
            exit(1);  
        }  
        return tmp;   
    }  
      
    template<class T>  
    inline void _deallocate(T* buffer)  
    {  
        ::operator delete(buffer);  
    }  
    /************************************new的三种形态******************************************* 
    ****new operator:就是平常用的new，通常做三件事，1.用operator new分配内存给对象，2.调用构造函数初始化那块内存，3.将地址转给对象指针  
                     如果仅仅是在堆上建立对象，那么应该使用new operator，它会提供周全的服务   
    ****operator new:在默认情况下首先会调用分配内存的代码，尝试从堆上得到一段空间，成功就返回，失败就调用new_hander，重复前面过程，直到抛出异常  
                     如果仅仅是分配内存，那么应该调用operator new，但初始化不在它的职责之内。若对默认的内存分配过程不满意，那就重载它  
    ****placement new:用来实现定位构造，可以通过它来选择合适的构造函数。  
                     如果想在一块已获得的内存里建立一个对象，那就改用placement new  
    ********************************************************************************************/  
    template<class T1,class T2>  
    inline void _construct(T1* p,const T2& val)  
    {  
        new(p) T1(val);//p为那块内存地址，T1()为指定构造函数；此句为p->T1::T1(val);   
        std::cout<<"I'm _construct!"<<std::endl;  
    }  
      
    template<class T>  
    inline void _destroy(T* ptr)  
    {  
        std::cout<<"I'm _destroy!"<<std::endl;  
        ptr->~T();  
    }  
      
    template<class T>  
    class mallocator  
    {  
        public:  
            typedef T value_type;//为什么要重新定义，原因在章三  
            typedef T* pointer;  
            typedef const T* const_pointer;  
            typedef T& reference;  
            typedef const T& const_reference;  
            typedef size_t size_type;  
            typedef ptrdiff_t difference_type;  
          
          
            template<class U>  
            struct rebind//干吗用？见下   
            {  
                typedef mallocator<U> mother;  
            };   
              
            pointer allocate(size_type n,const void* hint=0)  
            {  
                return _allocate((difference_type)n,(pointer)0);  
            }  
              
            void deallocate(pointer p,size_type n)  
            {  
                _deallocate(p);  
            }  
              
            void construct(pointer p,const_reference val)  
            {  
                _construct(p,val);  
            }  
              
            void destroy(pointer p)  
            {  
                _destroy(p);  
            }  
              
            pointer address(reference x)  
            {  
                return (pointer)&x;  
            }  
              
            const pointer const_address(const_reference x)  
            {  
                return (const pointer)&x;  
            }  
              
            size_type max_size()const  
            {  
                return size_type(UINT_MAX/sizeof(value_type));  
            }  
    };  
}  
#endif 