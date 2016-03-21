#include <iostream>
#include <string>


#include <typeinfo>
using namespace std;

#if defined(__SGI_STL_USE_AutoPtr_CONVERSIONS) && \
    defined(__STL_MEMBER_TEMPLATES)

template<class U>
struct AutoPtrRef
{
  U* m_pointee;

  AutoPtrRef(U* p)
  :m_pointee(p)
  {

  }

};

#endif /* auto ptr conversions && member templates */

template<class T>
class AutoPtr
{
public :
    /// constructor
    explicit AutoPtr(T *p = NULL)
    :m_pointee(p)
    {
        /// NOP
    }

    /// copy constructor
    template<class U>
    AutoPtr(AutoPtr<U> &rhs)    //  由于要释放rhs指针的指向， 因此参数不能为const
    :m_pointee(rhs.release())
    {
        /// NOP
    }

    ///
    ~AutoPtr()
    {
        delete this->m_pointee;
    }

    ///
    ///  基本操作 获取get, release释放, 重置reset
    ///

    ///  获取指针的指向
    T* get( ) const
    {
        return m_pointee;
    }

    ///  释放指针的指向
    T* release( )
    {
        T *temp = this->m_pointee;  //  保存原指向地址
        this->m_pointee = NULL;     //  将指针指空

        ///     内存的释放由析构函数完成
        return temp;
    }

    /// 重置指针的指向
    void reset(T *p)
    {
        if(m_pointee != p)
        {
            delete m_pointee;       //  释放原来的空间
            this->m_pointee = p;    //  修改指向
        }
    }

    ///
    ///  重载操作符
    ///

    /// *ptr取地址
    T& operator*( ) const
    {
        if(m_pointee == NULL)
        {
            std::cout <<"pointee is NULL..." <<std::endl;
        }
        return *m_pointee;
//        try
//        {
//            typeid(*m_pointee).name();
//
//            return *m_pointee;
//        }
//        catch(std::bad_typeid)
//        {
//           std::cout <<__LINE__ <<std::endl;
//           cout << "Object is NULL" << endl;
//        }
    }

    ///  指针指向->
    T*  operator->( ) const
    {
        return m_pointee;
    }

    template<class U>
    AutoPtr& operator=(AutoPtr<U> &ptr)
    {
        ///  auto_pstr独占性的关键
        if(this->m_pointee != ptr.m_pointee)
        {
            //  由于要修改左值的指向
            delete this->m_pointee;

            this->m_pointee = ptr.m_pointee;
            ptr.release( );                             //  释放右值指针的指向

        }
        return *this;
    }

    ///
    ///  增加的引用接口
    ///
#if defined(__SGI_STL_USE_AutoPtr_CONVERSIONS) && \
    defined(__STL_MEMBER_TEMPLATES)
    /// 构造函数
    AutoPtr(AutoPtrRef<T> ref)
    : m_pointee(ref.m_pointee)
    {

    }

    //  运算符
    AutoPtr& operator=(AutoPtrRef<T> ref)
    {
        if (ref.m_pointee != this->get()) {
        delete m_pointee;
      m_pointee = ref.m_pointee;
    }
    return *this;
  }

    template <class U>
    operator AutoPtrRef<U>( )
    {
        return AutoPtrRef<U>(this->release());
    }

    template <class U>
    operator AutoPtr<U>( )
    {
        return AutoPtr<U>(this->release());
    }

#endif /* auto ptr conversions && member templates */

private :
    T   *m_pointee;
};


int main(void)
{

    AutoPtr<string> pstr1(new string("jeancheng"));

    AutoPtr<string> pstr2(new string("gatieme"));


    std::cout <<*pstr1 <<std::endl;
    std::cout <<*pstr2 <<std::endl;

    pstr1 = pstr2;

    std::cout <<*pstr1 <<std::endl;
    std::cout <<*pstr2 <<std::endl;           //  segment fault  -=> becase


    return 0;


}
