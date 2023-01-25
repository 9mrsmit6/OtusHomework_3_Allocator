#include <iostream>
#include "modules/simpleAllocator.h"
#include "modules/utils.hpp"
#include <vector>
#include <map>
#include <bitset>

struct AllocatorConfig
{
    static const int size{128};
};

int main()
{


    std::vector<int, SimpleAllocator<int,AllocatorConfig> > vector;


    auto m = std::map<int,float,std::less<int>,	SimpleAllocator<std::pair<	const int, float> , AllocatorConfig> >{};


    for (int i = 0; i < 10; ++i) {
        vector.push_back(i);
        m[i]=i;
    }

    for (const auto& v : vector)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
    std::cout << "MAP: ";
    for (int i=0;i!=10; i++)
    {
        std::cout << m[i] << ' ';
    }
    std::cout << std::endl;

    auto other = vector;

    for (const auto& v : other) {
        std::cout << v << ' ';
    }
    std::cout << std::endl;



//    auto base=std::bitset<16>(0b1110000011101111);
//    std::cout<<base<<std::endl;



////   auto index=Utils::getAllocationIndex<16>(base, 6);
////   if(!index)
////   {
////       std::cout<<"NO"<<std::endl;
////   }
////   else
////   {
////       std::cout<<"OK:"<<index.value()<<std::endl;

////   }








    return 0;
}
