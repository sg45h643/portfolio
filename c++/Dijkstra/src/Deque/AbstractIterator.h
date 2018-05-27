#ifndef ABSTRACT_ITERATOR_H
#define ABSTRACT_ITERATOR_H

#include <stdint.h>
#include <iostream>

namespace tango
{
    template<typename T>
    class AbstractIterator;
}

#include "AbstractDeque.h"
#include "Deque.h"

#define _block_size 10

namespace tango
{
    template<typename T>
    class AbstractIterator
    {
        public:
            virtual ~AbstractIterator() {}

            AbstractIterator& operator=(const AbstractIterator<T>& it);

        protected:
            virtual void previus(uint32_t n);
            virtual void next(uint32_t n);

        protected:
            Deque<T>* deque;
            T* tab;
            uint32_t n_tab;
            uint32_t offset;
    };

    template<typename T>
    AbstractIterator<T>& AbstractIterator<T>::operator=(const AbstractIterator<T>& it)
    {
        tab = it.tab;
        n_tab = it.n_tab;
        offset = it.offset;

        return *this;
    }

    template<typename T>
    void AbstractIterator<T>::previus(uint32_t n)
    {
        assert(tab);

        for(; _block_size <= n; n -= _block_size)
        {
            --n_tab;
            tab = deque->index[n_tab];
        }

        offset -= n;
    }

    template<typename T>
    void AbstractIterator<T>::next(uint32_t n)
    {
        assert(tab);

        for(; _block_size <= n; n -= _block_size)
        {
            ++n_tab;
            tab = deque->index[n_tab];
        }

        offset += n;
    }
}

#endif // ABSTRACT_ITERATOR_H
