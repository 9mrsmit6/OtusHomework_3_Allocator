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
        ~TestConteiner()
        {
            popNode=first;

            for(int i=0;i!=id;i++)
            {
                if(popNode==nullptr){break;}
                auto* nextNodePtr=popNode->nextNode;
                traits::destroy(alloc, popNode);
                traits::deallocate(alloc,popNode,1);
                popNode=nextNodePtr;
            }
        }

        void push(T&& addElement)
        {
            auto* nodePtr=traits::allocate(alloc, 1);
            if(nodePtr==nullptr)
            {
                return;
            }

            traits::construct(alloc,nodePtr, std::forward<T>(addElement));
            id++;


            if(pushNode!=nullptr)
            {
                pushNode->nextNode=nodePtr;
            }
            pushNode=nodePtr;

            if(first==nullptr)
            {
                first=nodePtr;
            }

            if(popNode==nullptr)
            {
                popNode=nodePtr;
            }

        }

        std::optional<T> next()
        {
            if(popNode==nullptr)
            {
                return std::nullopt;
            }

            auto& ret=popNode->element;
            popNode=popNode->nextNode;
            return ret;
        }



    private:
        TestContainerNode<T>* first{nullptr};
        TestContainerNode<T>* pushNode{nullptr};
        TestContainerNode<T>* popNode{nullptr};

        std::size_t id{0};

        Allocator alloc;

        using traits = std::allocator_traits<decltype(alloc)>;




};



#endif // CONTAINER_HPP
