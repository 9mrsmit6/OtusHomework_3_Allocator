#ifndef SIMPLEALLOCATOR_H
#define SIMPLEALLOCATOR_H
#include <memory>

template<typename T>
class SimpleAllocator
{
    using value_type= T;

    SimpleAllocator()   =   default;
    ~SimpleAllocator()  =   default;

    SimpleAllocator(const SimpleAllocator<T>&){}

   template <typename U>
   struct rebuind
   {
       using other=SimpleAllocator<U>;
   };

   T* allocate(std::size_t count_objects)
   {

   }

   void deallocate(T* ptr, std::size_t count_objects)
   {

   }

   template< typename U, typename... Args >
   void construct( U* p, Args&&... args )
   {
       new(p) U(std::forward(args)...);
   }

   template< class U >
   void destroy( U* p )
   {
       p->~U();
   }


};





#endif // SIMPLEALLOCATOR_H
