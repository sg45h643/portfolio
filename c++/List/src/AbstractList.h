#ifndef ABSTRACT_LIST_H
#define ABSTRACT_LIST_H

namespace tango
{
    template<typename T>
    class AbstractList;
}

#include "AbstractIterator.h"

#include "Iterator.h"
#include "ConstIterator.h"

namespace tango
{
    template<typename T>
    class AbstractList
    {
        public:
            virtual ~AbstractList() {}

            // Iterators

            virtual Iterator<T> begin() = 0;
            virtual const ConstIterator<T> begin() const = 0;
            virtual Iterator<T> finish() = 0;
            virtual const ConstIterator<T> finish() const = 0;
            virtual Iterator<T> end() = 0;
            virtual const ConstIterator<T> end() const = 0;

            // Capacity

            virtual bool empty() const = 0;
            virtual size_t size() const = 0;

            // Element access

            virtual T& head() = 0;
            virtual const T& head() const = 0;

            virtual T& tail() = 0;
            virtual const T& tail() const = 0;

            // Modifiers

            virtual void insertFront(const T& v) = 0;
            virtual void removeFront() = 0;
            virtual void insertBack(const T& v) = 0;
            virtual void removeBack() = 0;
            virtual void clear() = 0;

            virtual void insertBefore(const T& v, const Iterator<T>& it) = 0;
            virtual void insertAfter(const T& v, const Iterator<T>& it) = 0;
            virtual void remove(const Iterator<T>& it) = 0;

            // Operations

            virtual void swap(const Iterator<T>& it_one, const Iterator<T>& it_two) = 0;
    };
}

#endif // ABSTRACT_LIST_H
