#ifndef ABSTRACT_DEQUE_H
#define ABSTRACT_DEQUE_H

#include<stdint.h>

namespace tango
{
    template<typename T>
    class AbstractDeque;
}

#include "Iterator.h"
#include "ConstIterator.h"

namespace tango
{
    template<typename T>
    class AbstractDeque
    {
        public:
            virtual ~AbstractDeque() {}
            virtual AbstractDeque<T>& operator=(const AbstractDeque<T>& in);

            // Iterator

            virtual Iterator<T> begin() = 0;
            virtual const ConstIterator<T> cbegin() const = 0;
            virtual Iterator<T> finish() = 0;
            virtual const ConstIterator<T> cfinish() const = 0;
            virtual Iterator<T> end() = 0;
            virtual const ConstIterator<T> cend() const = 0;

            // Capacity

            virtual size_t size() const = 0;
            virtual void resize(size_t n) = 0;
            virtual bool empty() const = 0;
            virtual void shrink_to_fit() = 0;

            // Element Access

            virtual T& operator[](uint32_t key) = 0;
            virtual const T& operator[](uint32_t key) const = 0;
            virtual T& at(uint32_t key) = 0;
            virtual const T& at(uint32_t key) const = 0;
            virtual T& front() const = 0;
            virtual T& back() const = 0;

            // Modifiers

            virtual void assign(size_t n, const T& value) = 0;
            virtual void push_back(const T& value) = 0;
            virtual void push_front(const T& value) = 0;
            virtual void pop_back() = 0;
            virtual void pop_front() = 0;
            virtual void insert(Iterator<T> it, const T& value) = 0;
            virtual void erase(Iterator<T> it) = 0;
            virtual void clear() = 0;
    };

    template<typename T>
    AbstractDeque<T>& AbstractDeque<T>::operator=(const AbstractDeque<T>& in)
    {
        clear();

        for(uint32_t i = 0; i < in.size(); i++)
            push_back(in[i]);

        return *this;
    }
}

#endif // ABSTRACT_DEQUE_H
