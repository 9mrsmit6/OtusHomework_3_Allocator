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
    std::cout<<std::endl;

    printMap(copyMap,  "COPY");
    printMap(myAllocatorMap,  "MYC ");

    std::cout<<"----------------------------"<<std::endl;

    std::cout<<"------------- MOVE ---------"<<std::endl;

    auto testMap=std::move(myAllocatorMap);
    printMap(testMap,  "MOVE");
    printMap(myAllocatorMap,  "MYM ");
    std::cout<<std::endl;

    myAllocatorMap[5]=567;
    testMap[5]=765;

    printMap(testMap,  "MOVE");
    printMap(myAllocatorMap,  "MYM ");

    std::cout<<"----------------------------"<<std::endl;


    std::cout<<"------- MY CONTEINER -------"<<std::endl;

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




    return 0;
}
