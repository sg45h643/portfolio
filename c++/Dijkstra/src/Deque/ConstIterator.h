#ifndef CONST_INTERATOR_H
#define CONST_INTERATOR_H

namespace tango
{
    template<typename T>
    class ConstIterator;
}

#include "AbstractIterator.h"

#include "Deque.h"

namespace tango
{
    template<typename T>
    class ConstIterator:
        public AbstractIterator<T>
    {
        public:
            friend class Deque<T>;

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
            ConstIterator<T>& operator=(const ConstIterator<T> it);

            operator bool() const { return tab; }

        private:
            ConstIterator(const Deque<T>* _deque, T* _tab, uint32_t _n_tab, uint32_t _offset);
            ConstIterator(const ConstIterator<T>* it, int32_t n);

        private:
            using AbstractIterator<T>::previus;
            using AbstractIterator<T>::next;

            using AbstractIterator<T>::deque;
            using AbstractIterator<T>::tab;
            using AbstractIterator<T>::n_tab;
            using AbstractIterator<T>::offset;
    };

    template<typename T>
    ConstIterator<T>::~ConstIterator()
    {}

    template<typename T>
    ConstIterator<T>::ConstIterator(const Deque<T>* _deque, T* _tab, uint32_t _n_tab, uint32_t _offset)
    {
        deque = const_cast<Deque<T>*>(_deque);
        tab = _tab;
        n_tab = _n_tab;
        offset = _offset;
    }

    template<typename T>
    ConstIterator<T>::ConstIterator(const ConstIterator<T>* it, int32_t n)
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
        ConstIterator<T> original = *this;
        previus(1);

        return *this;
    }

    template<typename T>
    const T& ConstIterator<T>::operator*() const
    {
        return tab[offset - 1];
    }

    template<typename T>
    const T* ConstIterator<T>::operator->() const
    {
        return &tab[offset - 1];
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
    ConstIterator<T>& ConstIterator<T>::operator=(const ConstIterator<T> it)
    {
        tab = it.tab;
        n_tab = it.n_tab;
        offset = it.offset;

        return *this;
    }
}

#endif // CONST_INTERATOR_H
