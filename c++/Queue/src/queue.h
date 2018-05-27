#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
#include <stdint.h>

namespace tango
{
    template<typename T>
    class Queue;
}

#include "abstract_queue.h"

namespace tango
{
    template<typename T>
    class Queue:
        public AbstractQueue<T>
    {
        private:
            class Node
            {
                public:
                    Node(const T& obj): object(obj), next(NULL) {}

                public:
                    T object;
                    Node* next;
            };

        public:
            Queue();
            Queue(const Queue& q);
            virtual ~Queue();

            void insert(const T& v);
            void remove();

            size_t size() const;
            bool empty() const;

            T& head();
            const T& head() const;

            T& tail();
            const T& tail() const;

            void clear();

            Queue& operator=(const Queue& q);

        private:
            void copy(const Queue& fromq);

        private:
            Node* first;
            Node* last;
            size_t amount;
    };

    template<typename T>
    Queue<T>::Queue():
        first(NULL),
        last(NULL),
        amount(0)
    {}

    template<typename T>
    Queue<T>::Queue(const Queue& q):
        first(NULL),
        last(NULL),
        amount(0)
    {
        copy(q);
    }

    template<typename T>
    Queue<T>::~Queue()
    {
        clear();
    }

    template<typename T>
    void Queue<T>::insert(const T& v)
    {
        Node* const n = new Node(v);

        if(amount)
        {
            assert(last);
            assert(last->next == NULL);

            last->next = n;
            last = n;
        }
        else
        {
            assert(first == NULL);
            assert(last == NULL);

            first = n;
            last  = n;
        }

        amount += 1;
    }

    template<typename T>
    void Queue<T>::remove()
    {
        switch(amount)
        {
            case 0:
                return;

            case 1:
            {
                assert(first);
                assert(last);
                assert(first == last);

                delete first;

                first = NULL;
                last = NULL;
            }
            break;

            default:
            {
                assert(first);

                Node* const n = first;

                first = first->next;
                delete n;
            }
            break;
        }

        amount -= 1;
    }

    template<typename T>
    size_t Queue<T>::size() const
    {
        return amount;
    }

    template<typename T>
    bool Queue<T>::empty() const
    {
        return amount == 0;
    }

    template<typename T>
    T& Queue<T>::head()
    {
        assert(amount && "empty queue");
        return first->object;
    }

    template<typename T>
    const T& Queue<T>::head() const
    {
        assert(amount && "empty queue");
        return first->object;
    }

    template<typename T>
    T& Queue<T>::tail()
    {
        assert(amount && "empty queue");
        return last->object;
    }

    template<typename T>
    const T& Queue<T>::tail() const
    {
        assert(amount && "empty queue");
        return last->object;
    }

    template<typename T>
    void Queue<T>::clear()
    {
        if(amount == 0)
            return;

#ifdef DEBUG
        size_t amnt = 0;
        Node* it = first;

        while(it)
        {
            amnt += 1;
            it    = it->next;
        }

        assert(amnt == amount);
#endif

        Node* n = first;
        Node* nn;

        while(n)
        {
            nn = n->next;
            delete n;
            n = nn;
        }

        first = NULL;
        last = NULL;
        amount = 0;
    }

    template<typename T>
    Queue<T>& Queue<T>::operator=(const Queue& q)
    {
        copy(q);
        return *this;
    }

    template<typename T>
    void Queue<T>::copy(const Queue& q)
    {
        clear();

        for(Node* n = q.first; n; n = n->next)
            insert(n->object);
    }
}

#endif // QUEUE_H
