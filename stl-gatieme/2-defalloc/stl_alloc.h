// Filename:    stl_alloc.h  
  

  
// 特别说明: SGI STL的allocator在我的编译环境下不使用内存池  
//          而其内存池不进行内存释放操作, 其释放时机为程序退出或者stack unwinding  
//          由操作系统保证内存的回收  
  
/* 
 * Copyright (c) 1996-1997 
 * Silicon Graphics Computer Systems, Inc. 
 * 
 * Permission to use, copy, modify, distribute and sell this software 
 * and its documentation for any purpose is hereby granted without fee, 
 * provided that the above copyright notice appear in all copies and 
 * that both that copyright notice and this permission notice appear 
 * in supporting documentation.  Silicon Graphics makes no 
 * representations about the suitability of this software for any 
 * purpose.  It is provided "as is" without express or implied warranty. 
 */  
  
/* NOTE: This is an internal header file, included by other STL headers. 
 *   You should not attempt to use it directly. 
 */  
  
#ifndef __SGI_STL_INTERNAL_ALLOC_H  
#define __SGI_STL_INTERNAL_ALLOC_H  
  
#ifdef __SUNPRO_CC  
#  define __PRIVATE public  
// SUN编译器对private限制过多, 需要开放权限  
#else  
#  define __PRIVATE private  
#endif  
  
// 为了保证兼容性, 对于不支持模板类静态成员的情况, 使用malloc()进行内存分配  
#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG  
#  define __USE_MALLOC  
#endif  
  
// 实现了一些标准的node allocator  
// 但是不同于C++标准或者STL原始STL标准  
// 这些allocator没有封装不同指针类型  
// 事实上我们假定只有一种指针理性  
// allocation primitives意在分配不大于原始STL allocator分配的独立的对象  
  
#if 0  
#   include <new>  
#   define __THROW_BAD_ALLOC throw bad_alloc  
#elif !defined(__THROW_BAD_ALLOC)  
#   include <iostream.h>  
#   define __THROW_BAD_ALLOC cerr << "out of memory" << endl; exit(1)  
#endif  
  
#ifndef __ALLOC  
#   define __ALLOC alloc  
#endif  
#ifdef __STL_WIN32THREADS  
#   include <windows.h>  
#endif  
  
#include <stddef.h>  
#include <stdlib.h>  
#include <string.h>  
#include <assert.h>  
#ifndef __RESTRICT  
#  define __RESTRICT  
#endif  
  
// 多线程支持  
// __STL_PTHREADS       // GCC编译器  
// _NOTHREADS           // 不支持多线程  
// __STL_SGI_THREADS    // SGI机器专用  
// __STL_WIN32THREADS   // MSVC编译器  
#if !defined(__STL_PTHREADS) && !defined(_NOTHREADS) \  
 && !defined(__STL_SGI_THREADS) && !defined(__STL_WIN32THREADS)  
#   define _NOTHREADS  
#endif  
  
# ifdef __STL_PTHREADS  
    // POSIX Threads  
    // This is dubious, since this is likely to be a high contention  
    // lock.   Performance may not be adequate.  
#   include <pthread.h>  
#   define __NODE_ALLOCATOR_LOCK \  
        if (threads) pthread_mutex_lock(&__node_allocator_lock)  
#   define __NODE_ALLOCATOR_UNLOCK \  
        if (threads) pthread_mutex_unlock(&__node_allocator_lock)  
#   define __NODE_ALLOCATOR_THREADS true  
#   define __VOLATILE volatile  // Needed at -O3 on SGI  
# endif  
# ifdef __STL_WIN32THREADS  
    // The lock needs to be initialized by constructing an allocator  
    // objects of the right type.  We do that here explicitly for alloc.  
#   define __NODE_ALLOCATOR_LOCK \  
        EnterCriticalSection(&__node_allocator_lock)  
#   define __NODE_ALLOCATOR_UNLOCK \  
        LeaveCriticalSection(&__node_allocator_lock)  
#   define __NODE_ALLOCATOR_THREADS true  
#   define __VOLATILE volatile  // may not be needed  
# endif /* WIN32THREADS */  
# ifdef __STL_SGI_THREADS  
    // This should work without threads, with sproc threads, or with  
    // pthreads.  It is suboptimal in all cases.  
    // It is unlikely to even compile on nonSGI machines.  
  
    extern "C" {  
      extern int __us_rsthread_malloc;  
    }  
    // The above is copied from malloc.h.  Including <malloc.h>  
    // would be cleaner but fails with certain levels of standard  
    // conformance.  
#   define __NODE_ALLOCATOR_LOCK if (threads && __us_rsthread_malloc) \  
                { __lock(&__node_allocator_lock); }  
#   define __NODE_ALLOCATOR_UNLOCK if (threads && __us_rsthread_malloc) \  
                { __unlock(&__node_allocator_lock); }  
#   define __NODE_ALLOCATOR_THREADS true  
#   define __VOLATILE volatile  // Needed at -O3 on SGI  
# endif  
# ifdef _NOTHREADS  
//  Thread-unsafe  
#   define __NODE_ALLOCATOR_LOCK  
#   define __NODE_ALLOCATOR_UNLOCK  
#   define __NODE_ALLOCATOR_THREADS false  
#   define __VOLATILE  
# endif  
  
__STL_BEGIN_NAMESPACE  
  
#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)  
#pragma set woff 1174  
#endif  
  
// Malloc-based allocator.  Typically slower than default alloc below.  
// Typically thread-safe and more storage efficient.  
#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG  
# ifdef __DECLARE_GLOBALS_HERE  
    void (* __malloc_alloc_oom_handler)() = 0;  
    // g++ 2.7.2 does not handle static template data members.  
# else  
    extern void (* __malloc_alloc_oom_handler)();  
# endif  
#endif  
  
// 一级配置器  
template <int inst>  
class __malloc_alloc_template  
{  
private:  
    // 用于在设置了__malloc_alloc_oom_handler情况下循环分配内存,  
    // 直到成功分配  
    static void *oom_malloc(size_t);  
    static void *oom_realloc(void *, size_t);  
  
    // 如果编译器支持模板类静态成员, 则使用错误处理函数, 类似C++的set_new_handler()  
    // 默认值为0, 如果不设置, 则内存分配失败时直接__THROW_BAD_ALLOC  
#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG  
    static void (* __malloc_alloc_oom_handler)();  
#endif  
  
public:  
    // 分配指定大小的内存(size_t n)， 如果分配失败, 则进入循环分配阶段  
    // 循环分配前提是要保证正确设置了__malloc_alloc_oom_handler  
    static void * allocate(size_t n)  
    {  
        void *result = malloc(n);  
        if (0 == result) result = oom_malloc(n);  
        return result;  
    }  
  
    // 后面的size_t是为了兼容operator delele  
    static void deallocate(void *p, size_t /* n */)  
    { free(p); }  
  
    // 重新分配内存大小, 第二个参数是为了兼容operator new  
    static void * reallocate(void *p, size_t /* old_sz */, size_t new_sz)  
    {  
        void * result = realloc(p, new_sz);  
        if (0 == result) result = oom_realloc(p, new_sz);  
        return result;  
    }  
  
    // 设置错误处理函数, 返回原来的函数指针  
    // 不属于C++标准规定的接口  
    static void (* set_malloc_handler(void (*f)()))()  
    {  
        void (* old)() = __malloc_alloc_oom_handler;  
        __malloc_alloc_oom_handler = f;  
        return(old);  
    }  
};  
  
// malloc_alloc out-of-memory handling  
  
#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG  
template <int inst>  
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;  
#endif  
  
// 如果设置了__malloc_alloc_oom_handler, 则首先执行错误处理函数, 然后循环分配直到成功  
// 如果未设置__malloc_alloc_oom_handler, __THROW_BAD_ALLOC  
template <int inst>  
void * __malloc_alloc_template<inst>::oom_malloc(size_t n)  
{  
    void (* my_malloc_handler)();  
    void *result;  
  
    for (;;) {  
        my_malloc_handler = __malloc_alloc_oom_handler;  
        if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }  
        (*my_malloc_handler)();  
        result = malloc(n);  
        if (result) return(result);  
    }  
}  
  
template <int inst>  
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)  
{  
    void (* my_malloc_handler)();  
    void *result;  
  
    for (;;) {  
        my_malloc_handler = __malloc_alloc_oom_handler;  
        if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }  
        (*my_malloc_handler)();  
        result = realloc(p, n);  
        if (result) return(result);  
    }  
}  
  
// 这个版本的STL并没有使用non-type模板参数  
typedef __malloc_alloc_template<0> malloc_alloc;  
  
// 这个类中的接口其实就是STL标准中的allocator的接口  
// 实际上所有的SGI STL都使用这个进行内存配置  
// 例如: stl_vector.h中  
// template <class T, class Alloc = alloc>  
// class vector  
// {  
//      ...  
// protected:  
//      typedef simple_alloc<value_type, Alloc> data_allocator;  
//      ...  
//};  
template<class T, class Alloc>  
class simple_alloc  
{  
public:  
    static T *allocate(size_t n)  
                { return 0 == n? 0 : (T*) Alloc::allocate(n * sizeof (T)); }  
    static T *allocate(void)  
                { return (T*) Alloc::allocate(sizeof (T)); }  
    static void deallocate(T *p, size_t n)  
                { if (0 != n) Alloc::deallocate(p, n * sizeof (T)); }  
    static void deallocate(T *p)  
                { Alloc::deallocate(p, sizeof (T)); }  
};  
  
// Allocator adaptor to check size arguments for debugging.  
// Reports errors using assert.  Checking can be disabled with  
// NDEBUG, but it's far better to just use the underlying allocator  
// instead when no checking is desired.  
// There is some evidence that this can confuse Purify.  
template <class Alloc>  
class debug_alloc  
{  
private:  
    enum {extra = 8};       // Size of space used to store size.  Note  
                            // that this must be large enough to preserve  
                            // alignment.  
  
public:  
  
    // extra 保证不会分配为0的内存空间, 而且要保证内存对齐  
    // 把分配内存的最前面设置成n的大小, 用于后面校验  
    // 内存对齐的作用就是保护前面extra大小的数据不被修改  
    static void * allocate(size_t n)  
    {  
        char *result = (char *)Alloc::allocate(n + extra);  
        *(size_t *)result = n;  
        return result + extra;  
    }  
  
    // 如果*(size_t *)real_p != n则肯定发生向前越界  
    static void deallocate(void *p, size_t n)  
    {  
        char * real_p = (char *)p - extra;  
        assert(*(size_t *)real_p == n);  
        Alloc::deallocate(real_p, n + extra);  
    }  
  
    static void * reallocate(void *p, size_t old_sz, size_t new_sz)  
    {  
        char * real_p = (char *)p - extra;  
        assert(*(size_t *)real_p == old_sz);  
        char * result = (char *)  
                      Alloc::reallocate(real_p, old_sz + extra, new_sz + extra);  
        *(size_t *)result = new_sz;  
        return result + extra;  
    }  
};  
  
# ifdef __USE_MALLOC  
  
typedef malloc_alloc alloc;  
typedef malloc_alloc single_client_alloc;  
  
# else  
  
// 默认的node allocator  
// 如果有合适的编译器, 速度上与原始的STL class-specific allocators大致等价  
// 但是具有产生更少内存碎片的优点  
// Default_alloc_template参数是用于实验性质的, 在未来可能会消失  
// 客户只能在当下使用alloc  
//  
// 重要的实现属性:  
// 1. 如果客户请求一个size > __MAX_BYTE的对象, 则直接使用malloc()分配  
// 2. 对于其它情况下, 我们将请求对象的大小按照内存对齐向上舍入ROUND_UP(requested_size)  
// TODO: 待翻译  
// 2. In all other cases, we allocate an object of size exactly  
//    ROUND_UP(requested_size).  Thus the client has enough size  
//    information that we can return the object to the proper free list  
//    without permanently losing part of the object.  
//  
  
// 第一个模板参数指定是否有多于一个线程使用本allocator  
// 在一个default_alloc实例中分配对象, 在另一个deallocate实例中释放对象, 是安全的  
// 这有效的转换其所有权到另一个对象  
// 这可能导致对我们引用的区域产生不良影响  
// 第二个模板参数仅仅用于创建多个default_alloc实例  
// 不同容器使用不同allocator实例创建的node拥有不同类型, 这限制了此方法的通用性  
  
// Sun C++ compiler需要在类外定义这些枚举  
#ifdef __SUNPRO_CC  
// breaks if we make these template class members:  
  enum {__ALIGN = 8};  
  enum {__MAX_BYTES = 128};  
  enum {__NFREELISTS = __MAX_BYTES/__ALIGN};  
#endif  
  
template <bool threads, int inst>  
class __default_alloc_template  
{  
private:  
  // Really we should use static const int x = N  
  // instead of enum { x = N }, but few compilers accept the former.  
# ifndef __SUNPRO_CC  
    enum {__ALIGN = 8};  
    enum {__MAX_BYTES = 128};  
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN};  
# endif  
    // 向上舍入操作  
    // 解释一下, __ALIGN - 1指明的是实际内存对齐的粒度  
    // 例如__ALIGN = 8时, 我们只需要7就可以实际表示8个数(0~7)  
    // 那么~(__ALIGN - 1)就是进行舍入的粒度  
    // 我们将(bytes) + __ALIGN-1)就是先进行进位, 然后截断  
    // 这就保证了我是向上舍入的  
    // 例如byte = 100, __ALIGN = 8的情况  
    // ~(__ALIGN - 1) = (1 000)B  
    // ((bytes) + __ALIGN-1) = (1 101 011)B  
    // (((bytes) + __ALIGN-1) & ~(__ALIGN - 1)) = (1 101 000 )B = (104)D  
    // 104 / 8 = 13, 这就实现了向上舍入  
    // 对于byte刚好满足内存对齐的情况下, 结果保持byte大小不变  
    // 记得《Hacker's Delight》上面有相关的计算  
    // 这个表达式与下面给出的等价  
    // ((((bytes) + _ALIGN - 1) * _ALIGN) / _ALIGN)  
    // 但是SGI STL使用的方法效率非常高  
    static size_t ROUND_UP(size_t bytes)  
    {  
        return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));  
    }  
__PRIVATE:  
    // 管理内存链表用  
    // 为了尽最大可能减少内存的使用, 这里使用一个union  
    // 如果使用第一个成员, 则指向另一个相同的union obj  
    // 而如果使用第二个成员, 则指向实际的内存区域  
    // 这样就实现了链表结点只使用一个指针的大小空间, 却能同时做索引和指向内存区域  
    // 这个技巧性非常强, 值得学习  
    union obj  
    {  
        union obj * free_list_link;  
        char client_data[1];    /* The client sees this.        */  
    };  
private:  
# ifdef __SUNPRO_CC  
    static obj * __VOLATILE free_list[];  
        // Specifying a size results in duplicate def for 4.1  
# else  
    // 这里分配的free_list为16  
    // 对应的内存链容量分别为8, 16, 32 ... 128  
    static obj * __VOLATILE free_list[__NFREELISTS];  
# endif  
    // 根据待待分配的空间大小, 在free_list中选择合适的大小  
    static  size_t FREELIST_INDEX(size_t bytes)  
    {  
        return (((bytes) + __ALIGN-1)/__ALIGN - 1);  
    }  
  
  // Returns an object of size n, and optionally adds to size n free list.  
  static void *refill(size_t n);  
  // Allocates a chunk for nobjs of size "size".  nobjs may be reduced  
  // if it is inconvenient to allocate the requested number.  
  static char *chunk_alloc(size_t size, int &nobjs);  
  
  // 内存池  
  static char *start_free;      // 内存池起始点  
  static char *end_free;        // 内存池结束点  
  static size_t heap_size;      // 已经在堆上分配的空间大小  
  
// 下面三个条件编译给多线程条件下使用的锁提供必要支持  
# ifdef __STL_SGI_THREADS  
    static volatile unsigned long __node_allocator_lock;  
    static void __lock(volatile unsigned long *);  
    static inline void __unlock(volatile unsigned long *);  
# endif  
  
# ifdef __STL_PTHREADS  
    static pthread_mutex_t __node_allocator_lock;  
# endif  
  
# ifdef __STL_WIN32THREADS  
    static CRITICAL_SECTION __node_allocator_lock;  
    static bool __node_allocator_lock_initialized;  
  
  public:  
    __default_alloc_template() {  
    // This assumes the first constructor is called before threads  
    // are started.  
        if (!__node_allocator_lock_initialized) {  
            InitializeCriticalSection(&__node_allocator_lock);  
            __node_allocator_lock_initialized = true;  
        }  
    }  
  private:  
# endif  
  
    // 用于多线程环境下锁定操作用  
    class lock  
    {  
    public:  
        lock() { __NODE_ALLOCATOR_LOCK; }  
        ~lock() { __NODE_ALLOCATOR_UNLOCK; }  
    };  
    friend class lock;  
  
public:  
  /* n must be > 0      */  
  static void * allocate(size_t n)  
  {  
    obj * __VOLATILE * my_free_list;  
    obj * __RESTRICT result;  
  
    // 如果待分配对象大于__MAX_BYTES, 使用一级配置器分配  
    if (n > (size_t) __MAX_BYTES) {  
        return(malloc_alloc::allocate(n));  
    }  
    my_free_list = free_list + FREELIST_INDEX(n);  
    // Acquire the lock here with a constructor call.  
    // This ensures that it is released in exit or during stack  
    // unwinding.  
#       ifndef _NOTHREADS  
        /*REFERENCED*/  
        lock lock_instance;  
#       endif  
    result = *my_free_list;  
    // 如果是第一次使用这个容量的链表, 则分配此链表需要的内存  
    // 如果不是, 则判断内存吃容量, 不够则分配  
    if (result == 0) {  
        void *r = refill(ROUND_UP(n));  
        return r;  
    }  
    *my_free_list = result -> free_list_link;  
    return (result);  
  };  
  
  /* p may not be 0 */  
  static void deallocate(void *p, size_t n)  
  {  
    obj *q = (obj *)p;  
    obj * __VOLATILE * my_free_list;  
  
    // 对于大于__MAX_BYTES的对象, 因为采用的是一级配置器分配, 所以同样使用一级配置器释放  
    if (n > (size_t) __MAX_BYTES) {  
        malloc_alloc::deallocate(p, n);  
        return;  
    }  
    my_free_list = free_list + FREELIST_INDEX(n);  
    // acquire lock  
#       ifndef _NOTHREADS  
        /*REFERENCED*/  
        lock lock_instance;  
#       endif /* _NOTHREADS */  
    q -> free_list_link = *my_free_list;  
    *my_free_list = q;  
    // lock is released here  
  }  
  
  static void * reallocate(void *p, size_t old_sz, size_t new_sz);  
} ;  
  
typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;  
typedef __default_alloc_template<false, 0> single_client_alloc;  
  
// 每次分配一大块内存, 防止多次分配小内存块带来的内存碎片  
// 进行分配操作时, 根据具体环境决定是否加锁  
// 我们假定要分配的内存满足内存对齐要求  
template <bool threads, int inst>  
char*  
__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs)  
{  
    char * result;  
    size_t total_bytes = size * nobjs;  
    size_t bytes_left = end_free - start_free;  // 计算内存池剩余容量  
  
    // 如果内存池中剩余内存>=需要分配的内内存, 返回start_free指向的内存块,  
    // 并且重新设置内存池起始点  
    if (bytes_left >= total_bytes) {  
        result = start_free;  
        start_free += total_bytes;  
        return(result);  
    }  
    // 如果内存吃中剩余的容量不够分配, 但是能至少分配一个节点时,  
    // 返回所能分配的最多的节点, 返回start_free指向的内存块  
    // 并且重新设置内存池起始点  
    else if (bytes_left >= size) {  
        nobjs = bytes_left/size;  
        total_bytes = size * nobjs;  
        result = start_free;  
        start_free += total_bytes;  
        return(result);  
    }  
    // 内存池剩余内存连一个节点也不够分配  
    else {  
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);  
        // 将剩余的内存分配给指定的free_list[FREELIST_INDEX(bytes_left)]  
        if (bytes_left > 0) {  
            obj * __VOLATILE * my_free_list =  
                        free_list + FREELIST_INDEX(bytes_left);  
  
            ((obj *)start_free) -> free_list_link = *my_free_list;  
            *my_free_list = (obj *)start_free;  
        }  
        start_free = (char *)malloc(bytes_to_get);  
        // 分配失败, 搜索原来已经分配的内存块, 看是否有大于等于当前请求的内存块  
        if (0 == start_free) {  
            int i;  
            obj * __VOLATILE * my_free_list, *p;  
            // Try to make do with what we have.  That can't  
            // hurt.  We do not try smaller requests, since that tends  
            // to result in disaster on multi-process machines.  
            for (i = size; i <= __MAX_BYTES; i += __ALIGN) {  
                my_free_list = free_list + FREELIST_INDEX(i);  
                p = *my_free_list;  
                // 找到了一个, 将其加入内存池中  
                if (0 != p) {  
                    *my_free_list = p -> free_list_link;  
                    start_free = (char *)p;  
                    end_free = start_free + i;  
                    // 内存池更新完毕, 重新分配需要的内存  
                    return(chunk_alloc(size, nobjs));  
                    // Any leftover piece will eventually make it to the  
                    // right free list.  
                }  
            }  
  
            // 再次失败, 直接调用一级配置器分配, 期待异常处理函数能提供帮助  
            // 不过在我看来, 内存分配失败进行其它尝试已经没什么意义了,  
            // 最好直接log, 然后让程序崩溃  
        end_free = 0;   // In case of exception.  
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);  
        }  
        heap_size += bytes_to_get;  
        end_free = start_free + bytes_to_get;  
        // 内存池更新完毕, 重新分配需要的内存  
        return(chunk_alloc(size, nobjs));  
    }  
}  
  
  
// 返回一个大小为n的对象, 并且加入到free_list[FREELIST_INDEX(n)]  
// 进行分配操作时, 根据具体环境决定是否加锁  
// 我们假定要分配的内存满足内存对齐要求  
template <bool threads, int inst>  
void* __default_alloc_template<threads, inst>::refill(size_t n)  
{  
    int nobjs = 20;  
    char * chunk = chunk_alloc(n, nobjs);  
    obj * __VOLATILE * my_free_list;  
    obj * result;  
    obj * current_obj, * next_obj;  
    int i;  
  
    // 如果内存池仅仅只够分配一个对象的空间, 直接返回即可  
    if (1 == nobjs) return(chunk);  
  
    // 内存池能分配更多的空间  
    my_free_list = free_list + FREELIST_INDEX(n);  
  
    // 在chunk的空间中建立free_list  
      result = (obj *)chunk;  
      *my_free_list = next_obj = (obj *)(chunk + n);  
      for (i = 1; ; i++) {  
        current_obj = next_obj;  
        next_obj = (obj *)((char *)next_obj + n);  
        if (nobjs - 1 == i) {  
            current_obj -> free_list_link = 0;  
            break;  
        } else {  
            current_obj -> free_list_link = next_obj;  
        }  
      }  
    return(result);  
}  
  
template <bool threads, int inst>  
void*  
__default_alloc_template<threads, inst>::reallocate(void *p,  
                                                    size_t old_sz,  
                                                    size_t new_sz)  
{  
    void * result;  
    size_t copy_sz;  
  
    // 如果old_size和new_size均大于__MAX_BYTES, 则直接调用realloc()  
    // 因为这部分内存不是经过内存池分配的  
    if (old_sz > (size_t) __MAX_BYTES && new_sz > (size_t) __MAX_BYTES) {  
        return(realloc(p, new_sz));  
    }  
    // 如果ROUND_UP(old_sz) == ROUND_UP(new_sz), 内存大小没变化, 不进行重新分配  
    if (ROUND_UP(old_sz) == ROUND_UP(new_sz)) return(p);  
    // 进行重新分配并拷贝数据  
    result = allocate(new_sz);  
    copy_sz = new_sz > old_sz? old_sz : new_sz;  
    memcpy(result, p, copy_sz);  
    deallocate(p, old_sz);  
    return(result);  
}  
  
#ifdef __STL_PTHREADS  
    template <bool threads, int inst>  
    pthread_mutex_t  
    __default_alloc_template<threads, inst>::__node_allocator_lock  
        = PTHREAD_MUTEX_INITIALIZER;  
#endif  
  
#ifdef __STL_WIN32THREADS  
    template <bool threads, int inst> CRITICAL_SECTION  
    __default_alloc_template<threads, inst>::__node_allocator_lock;  
  
    template <bool threads, int inst> bool  
    __default_alloc_template<threads, inst>::__node_allocator_lock_initialized  
    = false;  
#endif  
  
#ifdef __STL_SGI_THREADS  
__STL_END_NAMESPACE  
#include <mutex.h>  
#include <time.h>  
__STL_BEGIN_NAMESPACE  
// Somewhat generic lock implementations.  We need only test-and-set  
// and some way to sleep.  These should work with both SGI pthreads  
// and sproc threads.  They may be useful on other systems.  
template <bool threads, int inst>  
volatile unsigned long  
__default_alloc_template<threads, inst>::__node_allocator_lock = 0;  
  
#if __mips < 3 || !(defined (_ABIN32) || defined(_ABI64)) || defined(__GNUC__)  
#   define __test_and_set(l,v) test_and_set(l,v)  
#endif  
  
template <bool threads, int inst>  
void  
__default_alloc_template<threads, inst>::__lock(volatile unsigned long *lock)  
{  
    const unsigned low_spin_max = 30;  // spin cycles if we suspect uniprocessor  
    const unsigned high_spin_max = 1000; // spin cycles for multiprocessor  
    static unsigned spin_max = low_spin_max;  
    unsigned my_spin_max;  
    static unsigned last_spins = 0;  
    unsigned my_last_spins;  
    static struct timespec ts = {0, 1000};  
    unsigned junk;  
#   define __ALLOC_PAUSE junk *= junk; junk *= junk; junk *= junk; junk *= junk  
    int i;  
  
    if (!__test_and_set((unsigned long *)lock, 1)) {  
        return;  
    }  
    my_spin_max = spin_max;  
    my_last_spins = last_spins;  
    for (i = 0; i < my_spin_max; i++) {  
        if (i < my_last_spins/2 || *lock) {  
            __ALLOC_PAUSE;  
            continue;  
        }  
        if (!__test_and_set((unsigned long *)lock, 1)) {  
            // got it!  
            // Spinning worked.  Thus we're probably not being scheduled  
            // against the other process with which we were contending.  
            // Thus it makes sense to spin longer the next time.  
            last_spins = i;  
            spin_max = high_spin_max;  
            return;  
        }  
    }  
    // We are probably being scheduled against the other process.  Sleep.  
    spin_max = low_spin_max;  
    for (;;) {  
        if (!__test_and_set((unsigned long *)lock, 1)) {  
            return;  
        }  
        nanosleep(&ts, 0);  
    }  
}  
  
template <bool threads, int inst>  
inline void  
__default_alloc_template<threads, inst>::__unlock(volatile unsigned long *lock)  
{  
#   if defined(__GNUC__) && __mips >= 3  
        asm("sync");  
        *lock = 0;  
#   elif __mips >= 3 && (defined (_ABIN32) || defined(_ABI64))  
        __lock_release(lock);  
#   else  
        *lock = 0;  
        // This is not sufficient on many multiprocessors, since  
        // writes to protected variables and the lock may be reordered.  
#   endif  
}  
#endif  
  
// 内存池起始位置  
template <bool threads, int inst>  
char *__default_alloc_template<threads, inst>::start_free = 0;  
// 内存池结束位置  
template <bool threads, int inst>  
char *__default_alloc_template<threads, inst>::end_free = 0;  
  
template <bool threads, int inst>  
size_t __default_alloc_template<threads, inst>::heap_size = 0;  
// 内存池容量索引数组  
template <bool threads, int inst>  
__default_alloc_template<threads, inst>::obj * __VOLATILE  
__default_alloc_template<threads, inst> ::free_list[  
# ifdef __SUNPRO_CC  
    __NFREELISTS  
# else  
    __default_alloc_template<threads, inst>::__NFREELISTS  
# endif  
] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };  
// The 16 zeros are necessary to make version 4.1 of the SunPro  
// compiler happy.  Otherwise it appears to allocate too little  
// space for the array.  
  
# ifdef __STL_WIN32THREADS  
  // Create one to get critical section initialized.  
  // We do this onece per file, but only the first constructor  
  // does anything.  
  static alloc __node_allocator_dummy_instance;  
# endif  
  
#endif /* ! __USE_MALLOC */  
  
#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)  
#pragma reset woff 1174  
#endif  
  
__STL_END_NAMESPACE  
  
#undef __PRIVATE  
  
#endif /* __SGI_STL_INTERNAL_ALLOC_H */  
  
// Local Variables:  
// mode:C++  
// End:  