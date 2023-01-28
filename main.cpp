#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <list>

#include "modules/simpleAllocator.h"
#include "modules/factorial.hpp"
#include "modules/container.hpp"

struct AllocatorConfig
{
    static const int size{10};
};

template<typename T, typename S>
void printMap(const T& map, S&& str)
{
    std::cout<<str<<": ";
    for(const auto& [key, value]:map)
    {
        std::cout<<'('<<key<<' '<<value<<") ";
    }
    std::cout<<std::endl;

}

template <typename T>
void fillMap(T& map )
{
    for(int i=0;i!=10;i++)
    {
        map[i]=Utils::factorial(i);
    }
}

int main()
{

    auto stdAllocatorMap = std::map<int,int>{};
    fillMap(stdAllocatorMap);

    auto myAllocatorMap = std::map<int,int, std::less<int>,SimpleAllocator<std::pair<const int, int> , AllocatorConfig> >{};
    fillMap(myAllocatorMap);

    printMap(stdAllocatorMap, "STD ");
    printMap(myAllocatorMap,  "MY  ");

    std::cout<<"------------- COPY ---------"<<std::endl;

    auto copyMap=myAllocatorMap;
    printMap(copyMap,  "COPY");
    printMap(myAllocatorMap,  "MYC ");

    myAllocatorMap[5]=321;
    copyMap[5]=123;

    printMap(copyMap,  "COPY");
    printMap(myAllocatorMap,  "MYC ");

    std::cout<<"----------------------------"<<std::endl;

    std::cout<<"------------- MOVE ---------"<<std::endl;

    auto testMap=std::move(myAllocatorMap);
    printMap(testMap,  "MOVE");
    printMap(myAllocatorMap,  "MYM ");
    myAllocatorMap[5]=567;
    testMap[5]=765;

    printMap(testMap,  "MOVE");
    printMap(myAllocatorMap,  "MYM ");

    std::cout<<"----------------------------"<<std::endl;




    TestConteiner<int> myConteiner;
    for(int i=0;i!=10;i++)
    {
        myConteiner.push(Utils::factorial(i));
    }

    for(int i=0;i!=10;i++)
    {
        auto v=myConteiner.next();
        if(v)
        {
            std::cout<<'('<<i<<' '<<v.value()<<") ";
        }
        else{break;}
    }
    std::cout<<std::endl;






//    std::allocator<TestContainerNode<int>> alloc;


//    auto v=alloc.allocate(1);
//    alloc.construct(v,123);

//    TestContainerNode<int>& vax= *v;

//    int* v1111 = new int(123);

//    new(v1111) int(123);

//    (*v1111)++;









//    std::vector<int, SimpleAllocator<int,AllocatorConfig> > vector;


//    auto m = std::map<int,float,std::less<int>,	SimpleAllocator<std::pair<	const int, float> , AllocatorConfig> >{};


//    for (int i = 0; i < 10; ++i) {
//        vector.push_back(i);
//        m[i]=i;
//    }

//    for (const auto& v : vector)
//    {
//        std::cout << v << ' ';
//    }
//    std::cout << std::endl;
//    std::cout << "MAP: ";
//    for (int i=0;i!=10; i++)
//    {
//        std::cout << m[i] << ' ';
//    }
//    std::cout << std::endl;

//    auto other = vector;

//    for (const auto& v : other) {
//        std::cout << v << ' ';
//    }
//    std::cout << std::endl;


//    auto value=128;

//    auto ptr=std::make_unique<int>(value);

//    std::list<std::unique_ptr<int>> list;

//    list.push_front(std::make_unique<int>(value));



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
