#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdint.h>
#include <assert.h>

namespace tango
{
    template<typename T>
    class Iterator;
}

#include "AbstractIterator.h"

#include "AbstractList.h"
#include "List.h"

namespace tango
{
    template<typename T>
    class Iterator:
        public AbstractIterator<T>
    {
        public:
            friend class List<T>;

        public:
            virtual ~Iterator();

            friend Iterator<T> operator+(const Iterator<T>& it, int32_t n) { return Iterator<T>(&it, n); }
            friend Iterator<T> operator+(int32_t n, const Iterator<T>& it) { return Iterator<T>(&it, n); }
            friend Iterator<T> operator-(const Iterator<T>& it, int32_t n) { return Iterator<T>(&it, -n); }

            Iterator<T>& operator++();
            Iterator<T> operator++(int32_t);
            Iterator<T>& operator--();
            Iterator<T> operator--(int32_t);

            T& operator*();
            const T& operator*() const;
            T* operator->();
            const T* operator->() const;

            Iterator<T>& operator+=(int32_t n);
            Iterator<T>& operator-=(int32_t n);
            Iterator<T>& operator=(const Iterator<T>& it);

            operator bool() const
            {
                return current_node;
            }

        private:
            Iterator(typename List<T>::Node* node);
            Iterator(const Iterator<T>* it, int32_t n);

            using AbstractIterator<T>::next;
            using AbstractIterator<T>::previus;
            using AbstractIterator<T>::current_node;
    };

    template<typename T>
    Iterator<T>::Iterator(typename List<T>::Node* node)
    {
        current_node = node;
    }

    template<typename T>
    Iterator<T>::Iterator(const Iterator<T>* it, int32_t n)
    {
        current_node = it->current_node;

        if(0 < n)
            next(n);
        else if(n < 0)
            previus(-n);
    }

    template<typename T>
    Iterator<T>::~Iterator()
    {}

    template<typename T>
    Iterator<T>& Iterator<T>::operator++()
    {
        next(1);

        return *this;
    }

    template<typename T>
    Iterator<T> Iterator<T>::operator++(int32_t)
    {
        Iterator<T> original = *this;

        next(1);

        return original;
    }

    template<typename T>
    Iterator<T>& Iterator<T>::operator--()
    {
        previus(1);

        return *this;
    }

    template<typename T>
    Iterator<T> Iterator<T>::operator--(int32_t)
    {
        Iterator<T> original = *this;

        previus(1);

        return original;
    }

    template<typename T>
    T& Iterator<T>::operator*()
    {
        return current_node->object;
    }

    template<typename T>
    const T& Iterator<T>::operator*() const
    {
        return current_node->object;
    }

    template<typename T>
    T* Iterator<T>::operator->()
    {
        return &current_node->object;
    }

    template<typename T>
    const T* Iterator<T>::operator->() const
    {
        return &current_node->object;
    }

    template<typename T>
    Iterator<T>& Iterator<T>::operator+=(int32_t n)
    {
        if(0 < n)
            next(n);
        else if(n < 0)
            previus(-n);

        return *this;
    }

    template<typename T>
    Iterator<T>& Iterator<T>::operator-=(int32_t n)
    {
        if(0 < n)
            previus(n);
        else if(n < 0)
            next(-n);

        return *this;
    }

    template<typename T>
    Iterator<T>& Iterator<T>::operator=(const Iterator<T>& it)
    {
        current_node = it.current_node;

        return *this;
    }
}

#endif // ITERATOR_H
