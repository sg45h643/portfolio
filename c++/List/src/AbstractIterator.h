#ifndef ABSTRACT_ITERATOR_H
#define ABSTRACT_ITERATOR_H

namespace tango
{
    template<typename T>
    class AbstractIterator;
}

#include "AbstractList.h"
#include "List.h"

namespace tango
{
    template<typename T>
    class AbstractIterator
    {
        public:
            virtual ~AbstractIterator() {}

        protected:
            typename List<T>::Node* current_node;

        protected:
            virtual void next(int32_t n);
            virtual void previus(int32_t n);
    };

    template<typename T>
    void AbstractIterator<T>::next(int32_t n)
    {
        assert(current_node);

        for(uint32_t i = 0; i < n; i++)
            if(current_node->next)
                current_node = current_node->next;
            else
            {
                current_node = NULL;
                break;
            }
    }

    template<typename T>
    void AbstractIterator<T>::previus(int32_t n)
    {
        assert(current_node);

        for(uint32_t i = 0; i < n; i++)
            if(current_node->previus)
                current_node = current_node->previus;
            else
            {
                current_node = NULL;
                break;
            }
    }
}

#endif // ABSTRACT_ITERATOR_H
