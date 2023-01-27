#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <memory>
#include <optional>



template<typename T>
struct TestContainerNode
{
    TestContainerNode<T>* nextNode;
    T element;

    TestContainerNode(T&& el)
    {
        new(&element) T(std::forward<T>(el));
        nextNode=nullptr;
    }

};


template <typename T, typename Allocator = std::allocator<TestContainerNode<T>>>
class TestConteiner
{
    public:

        TestConteiner():
            alloc()
        {
        }
        ~TestConteiner() = default;

        void add(T&& addElement)
        {
            auto* nodePtr=traits::allocate(alloc, 1);
            if(nodePtr==nullptr)
            {
                return;
            }

            traits::construct(alloc,nodePtr, std::forward<T>(addElement));


            last=nodePtr;

            if(current!=nullptr)
            {
                current->nextNode=nodePtr;
            }
            current=nodePtr;

            if(first==nullptr)
            {
                first=nodePtr;
            }
        }

//        std::optional<T&> getNext()
//        {
//            if(current==last){return std::nullopt;}

//        }



    private:
        TestContainerNode<T>* first;
        TestContainerNode<T>* current;
        TestContainerNode<T>* last;

        Allocator alloc;

        using traits = std::allocator_traits<decltype(alloc)>;




};



#endif // CONTAINER_HPP
