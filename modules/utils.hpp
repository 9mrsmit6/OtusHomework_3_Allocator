#ifndef UTILS_HPP
#define UTILS_HPP

#include <bitset>
#include <optional>

namespace Utils
{

    template<typename T, std::size_t blockSize>
    class MemoryBlock
    {
    public:
        MemoryBlock()
        {
            auto p = std::malloc(blockSize * sizeof(T));
            if (!p){ throw std::bad_alloc(); }
            memory=reinterpret_cast<T*>(p);
        };

        ~MemoryBlock()
        {
            std::free(memory);
        }

        std::optional<std::size_t> getAllocationIndex(std::size_t bytes)
        {

            if((info.size()-info.count())<bytes)
            {
                return std::nullopt;
            }

            auto mask=getBitMask(bytes);
            auto itCount=info.size()/bytes;

            for(auto i=0;i!=blockSize;i++)
            {
                auto rez=info&mask;
                if(rez.none())
                {
                    return std::optional{i};
                }
                mask<<=1;
            }
            return std::nullopt;
        }



        void freePionterIndex(T* pointer, std::size_t cnt)
        {
            bool isStart=false;
            for(auto i=0;i!=blockSize;i++)
            {
                if((&(memory[i])==pointer)&&(!isStart))
                {
                    setRange(i,cnt,0);
                    break;
                }
            }
        }

        void setRange(std::size_t start, std::size_t cnt, int v)
        {
            for(auto i=start;i!=(start+cnt);i++)
            {
                info[i]=v;
            }
        }

        T* getAdress(std::size_t index)
        {
            return &(memory[index]);
        }


    private:

        T* memory;

        std::bitset<blockSize> info{0};

        auto getBitMask(std::size_t cnt)
        {
            auto ret=std::bitset<blockSize>(0);
            for(std::size_t i=0;i!=cnt;i++)
            {
                ret.set(i);
            }
            return ret;
        }


};




}

#endif // UTILS_HPP
