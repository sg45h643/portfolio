#ifndef ABSTRACT_QUEUE_H
#define ABSTRACT_QUEUE_H

#include <stdio.h>

namespace tango
{
    template<typename T>
    class AbstractQueue;
}

namespace tango
{
    template<typename T>
    class AbstractQueue
    {
        public:
            virtual ~AbstractQueue() {}

            virtual void insert(const T& v) = 0;
            virtual void remove() = 0;

            virtual size_t size() const = 0;
            virtual bool empty() const = 0;

            virtual T& head() = 0;
            virtual const T& head() const = 0;

            virtual T& tail() = 0;
            virtual const T& tail() const = 0;

            virtual void clear() = 0;
    };
}

#endif // ABSTRACT_QUEUE_H
