#ifndef ITERATOR_H
#define ITERATOR_H

namespace tango
{
    template<typename T>
    class Iterator;
}

#include "AbstractIterator.h"

#include "Deque.h"

#include <iostream>

namespace tango
{
    template<typename T>
    class Iterator:
        public AbstractIterator<T>
    {
        public:
            friend class Deque<T>;

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
            Iterator<T>& operator=(const Iterator<T> it);

            operator bool() const
            {
                return tab;
            }

        private:
            Iterator(Deque<T>* _deque, T* _tab, uint32_t _n_tab, uint32_t _offset);
            Iterator(const Iterator<T>* it, int32_t n);

        private:
            using AbstractIterator<T>::previus;
            using AbstractIterator<T>::next;

            using AbstractIterator<T>::deque;
            using AbstractIterator<T>::tab;
            using AbstractIterator<T>::n_tab;
            using AbstractIterator<T>::offset;
    };

    template<typename T>
    Iterator<T>::~Iterator()
    {}

    template<typename T>
    Iterator<T>::Iterator(Deque<T>* _deque, T* _tab, uint32_t _n_tab, uint32_t _offset)
    {
        deque = _deque;
        tab = _tab;
        n_tab = _n_tab;
        offset = _offset;
    }

    template<typename T>
    Iterator<T>::Iterator(const Iterator<T>* it, int32_t n)
    {
        deque = it->deque;
        tab = it->tab;
        n_tab = it->n_tab;
        offset = it->offset;

        if(0 < n)
            next(n);
        else if(n < 0)
            previus(-n);
    }

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

        return *this;
    }

    template<typename T>
    T& Iterator<T>::operator*()
    {
        assert(tab);

        return tab[offset - 1];
    }

    template<typename T>
    const T& Iterator<T>::operator*() const
    {
        assert(tab);

        return tab[offset - 1];
    }

    template<typename T>
    T* Iterator<T>::operator->()
    {
        assert(tab);

        return &tab[offset - 1];
    }

    template<typename T>
    const T* Iterator<T>::operator->() const
    {
        assert(tab);

        return &tab[offset - 1];
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
    Iterator<T>& Iterator<T>::operator=(const Iterator<T> it)
    {
        tab = it.tab;
        n_tab = it.n_tab;
        offset = it.offset;

        return *this;
    }
}

#endif // ITERATOR_H
