#ifndef SIMPLEALLOCATOR_H
#define SIMPLEALLOCATOR_H
#include <memory>
#include <cstdlib>
#include <bitset>
#include "utils.hpp"
#include <iostream>
#include <list>




template<typename T, typename L>
class SimpleAllocator
{
public:
    using value_type= T;

    SimpleAllocator()
    {
        mem=std::make_unique<Utils::MemoryBlock<T, L::size >>();
    }
    ~SimpleAllocator()  =   default;

    template <typename U>
    SimpleAllocator(const SimpleAllocator<U,L>&)
    {

    }

    SimpleAllocator(const SimpleAllocator<T,L>&):
        SimpleAllocator()
    {

    }

   template <typename U>
   struct rebuind
   {
       using other=SimpleAllocator<U,L>;
   };

   T* allocate(std::size_t n);
   void deallocate(T* p, std::size_t n);

private:
   std::unique_ptr<Utils::MemoryBlock<T, L::size >> mem;

};

template <class T, class U, typename L >
constexpr bool operator== (const SimpleAllocator<T,L>&, const SimpleAllocator<U,L>&) noexcept {	return false;   }

template <class T, class U, typename L>
constexpr bool operator!= (const SimpleAllocator<T,L>&, const SimpleAllocator<U,L>&) noexcept {	return false;   }


template <typename T,typename L >
T* SimpleAllocator<T,L>::allocate(std::size_t n)
{
    auto p=mem->getAllocationIndex(n);
    if(!p){throw std::bad_alloc();}

    auto addr=mem->getAdress(p.value());
    mem->setRange(p.value(),n,1);

    return addr;
}

template <typename T,typename L >
void SimpleAllocator<T,L>::deallocate(T* p, std::size_t n)
{
    mem->freePionterIndex(p, n);    
}




#endif // SIMPLEALLOCATOR_H
