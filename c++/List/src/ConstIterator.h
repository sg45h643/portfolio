#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <stdint.h>
#include <assert.h>

namespace tango
{
    template<typename T>
    class ConstIterator;
}

#include "AbstractIterator.h"

#include "AbstractList.h"
#include "List.h"

namespace tango
{
    template<typename T>
    class ConstIterator:
        public AbstractIterator<T>
    {
        public:
            friend class List<T>;

        public:
            virtual ~ConstIterator();

            friend ConstIterator<T> operator+(const ConstIterator<T>& it, int32_t n) { return ConstIterator<T>(&it, n); }
            friend ConstIterator<T> operator+(int32_t n, const ConstIterator<T>& it) { return ConstIterator<T>(&it, n); }
            friend ConstIterator<T> operator-(const ConstIterator<T>& it, int32_t n) { return ConstIterator<T>(&it, -n); }

            ConstIterator<T>& operator++();
            ConstIterator<T> operator++(int32_t);
            ConstIterator<T>& operator--();
            ConstIterator<T> operator--(int32_t);

            const T& operator*() const;
            const T* operator->() const;

            ConstIterator<T>& operator+=(int32_t n);
            ConstIterator<T>& operator-=(int32_t n);
            ConstIterator<T>& operator=(const ConstIterator<T>& it);

            operator bool() const { return current_node; }

        private:
            ConstIterator(typename List<T>::Node* node);
            ConstIterator(const ConstIterator<T>* it, int32_t n);

            using AbstractIterator<T>::next;
            using AbstractIterator<T>::previus;
            using AbstractIterator<T>::current_node;
    };

    template<typename T>
    ConstIterator<T>::ConstIterator(typename List<T>::Node* node)
    {
        current_node = node;
    }

    template<typename T>
    ConstIterator<T>::ConstIterator(const ConstIterator<T>* it, int32_t n)
    {
        current_node = it->current_node;

        if(0 < n)
            next(n);
        else if(n < 0)
            previus(-n);
    }

    template<typename T>
    ConstIterator<T>::~ConstIterator()
    {}

    template<typename T>
    ConstIterator<T>& ConstIterator<T>::operator++()
    {
        next(1);

        return *this;
    }

    template<typename T>
    ConstIterator<T> ConstIterator<T>::operator++(int32_t)
    {
        ConstIterator<T> original = *this;

        next(1);

        return original;
    }

    template<typename T>
    ConstIterator<T>& ConstIterator<T>::operator--()
    {
        previus(1);

        return *this;
    }

    template<typename T>
    ConstIterator<T> ConstIterator<T>::operator--(int32_t)
    {
        ConstIterator original = *this;

        previus(1);

        return original;
    }

    template<typename T>
    const T& ConstIterator<T>::operator*() const
    {
        return current_node->object;
    }

    template<typename T>
    const T* ConstIterator<T>::operator->() const
    {
        return &current_node->object;
    }

    template<typename T>
    ConstIterator<T>& ConstIterator<T>::operator+=(int32_t n)
    {
        if(0 < n)
            next(n);
        else if(n < 0)
            previus(-n);

        return *this;
    }

    template<typename T>
    ConstIterator<T>& ConstIterator<T>::operator-=(int32_t n)
    {
        if(0 < n)
            previus(n);
        else if(n < 0)
            next(-n);

        return *this;
    }

    template<typename T>
    ConstIterator<T>& ConstIterator<T>::operator=(const ConstIterator<T>& it)
    {
        current_node = it.current_node;

        return *this;
    }
}

#endif // CONST_ITERATOR_H
