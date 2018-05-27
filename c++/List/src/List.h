#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

namespace tango
{
    template<typename T>
    class List;
}

#include "AbstractList.h"

#include "AbstractIterator.h"
#include "Iterator.h"
#include "ConstIterator.h"

namespace tango
{
    template<typename T>
    class List:
        public AbstractList<T>
    {
        public:
            friend class AbstractIterator<T>;
            friend class Iterator<T>;
            friend class ConstIterator<T>;

        private:
            class Node
            {
                public:
                    Node(const T& obj) : object(obj), previus(NULL), next(NULL) {}

                public:
                    T object;

                    Node* previus;
                    Node* next;
            };

        public:
            List();
            List(const List& in);
            virtual ~List();

            List& operator= (const List& in);

            Iterator<T> begin();
            const ConstIterator<T> begin() const;
            Iterator<T> finish();
            const ConstIterator<T> finish() const;
            Iterator<T> end();
            const ConstIterator<T> end() const;

            bool empty() const;
            size_t size() const;

            T& head();
            const T& head() const;

            T& tail();
            const T& tail() const;

            void insertFront(const T& v);
            void removeFront();
            void insertBack(const T& v);
            void removeBack();
            void insertBefore(const T& v, const Iterator<T>& it);
            void insertAfter(const T& v, const Iterator<T>& it);
            void remove(const Iterator<T>& it);
            void clear();

            void swap(const Iterator<T>& it_one, const Iterator<T>& it_two);

        private:
            void copy(const List& v);

        private:
            Node* first;
            Node* last;
            uint32_t amount;
    };

    template<typename T>
    List<T>::List() :
        first(NULL),
        last(NULL),
        amount(0)
    {}

    template<typename T>
    List<T>::List(const List& in) :
        first(NULL),
        last(NULL),
        amount(0)
    {
        copy(in);
    }

    template<typename T>
    List<T>::~List()
    {
        clear();
    }

    template<typename T>
    List<T>& List<T>::operator= (const List& in)
    {
        clear();
        copy(in);

        return *this;
    }

    template<typename T>
    Iterator<T> List<T>::begin()
    {
        return Iterator<T>(first);
    }

    template<typename T>
    const ConstIterator<T> List<T>::begin() const
    {
        return ConstIterator<T>(first);
    }

    template<typename T>
    Iterator<T> List<T>::finish()
    {
        return Iterator<T>(last);
    }

    template<typename T>
    const ConstIterator<T> List<T>::finish() const
    {
        return ConstIterator<T>(last);
    }

    template<typename T>
    Iterator<T> List<T>::end()
    {
        return Iterator<T>(NULL);
    }

    template<typename T>
    const ConstIterator<T> List<T>::end() const
    {
        return ConstIterator<T>(NULL);
    }

    template<typename T>
    bool List<T>::empty() const
    {
        return amount == 0;
    }

    template<typename T>
    size_t List<T>::size() const
    {
        return amount;
    }

    template<typename T>
    T& List<T>::head()
    {
        assert(amount);

        return first->object;
    }

    template<typename T>
    const T& List<T>::head() const
    {
        assert(amount);

        return first->object;
    }

    template<typename T>
    T& List<T>::tail()
    {
        assert(amount);

        return last->object;
    }

    template<typename T>
    const T& List<T>::tail() const
    {
        assert(amount);

        return last->object;
    }

    template<typename T>
    void List<T>::insertFront(const T& v)
    {
        if(amount)
        {
            Node* current = new Node(v);
            current->next = first;
            first->previus = current;
            first = current;
        }
        else
        {
            first = new Node(v);
            last = first;
        }

        amount++;
    }

    template<typename T>
    void List<T>::removeFront()
    {
        switch(amount)
        {
            case 0:
                return;
                break;

            case 1:
                delete first;
                first = NULL;
                last = NULL;
                break;

            default:
                Node* current = first->next;
                delete first;
                current->previus = NULL;
                first = current;
                break;
        }

        amount--;
    }

    template<typename T>
    void List<T>::insertBack(const T& v)
    {
        if(amount)
        {
            Node* current = new Node(v);
            last->next = current;
            current->previus = last;
            last = current;
        }
        else
        {
            last = new Node(v);
            first = last;
        }

        amount++;
    }

    template<typename T>
    void List<T>::removeBack()
    {
        switch(amount)
        {
            case 0:
                return;
                break;

            case 1:
                delete last;
                first = NULL;
                last = NULL;
                break;

            default:
                Node* current = last->previus;
                delete last;
                current->next = NULL;
                last = current;
                break;
        }

        amount--;
    }

    template<typename T>
    void List<T>::clear()
    {
        if(!amount)
            return;

        Node* current = last;

        while(amount)
        {
            last = current;
            current = current->previus;
            delete last;
            amount--;
        }

        first = NULL;
        last = NULL;
    }

    template<typename T>
    void List<T>::insertBefore(const T& v, const Iterator<T>& it)
    {
        if(!amount)
            return;

        Node* current = it.current_node;

        if(current == first)
        {
            current->previus = new Node(v);
            current->previus->next = current;
            first = current->previus;
        }
        else if(current)
        {
            Node* prev_old = current->previus;
            current->previus = new Node(v);
            current->previus->next = current;
            current->previus->previus = prev_old;
            prev_old->next = current->previus;
        }
        else
        {
            insertBack(v);
            return;
        }

        amount++;
    }

    template<typename T>
    void List<T>::insertAfter(const T& v, const Iterator<T>& it)
    {
        if(!amount)
            return;

        Node* current = it.current_node;

        if(current == last)
        {
            current->next = new Node(v);
            current->next->previus = current;
            last = current->next;
        }
        else if(current)
        {
            Node* after_old = current->next;
            current->next = new Node(v);
            current->next->previus = current;
            current->next->next = after_old;
            after_old->previus = current->next;
        }
        else
            return;

        amount++;
    }

    template<typename T>
    void List<T>::remove(const Iterator<T>& it)
    {
        if(!it.current_node)
            return;

        Node* current = it.current_node;

        if(current == first)
        {
            first = current->next;
            first->previus = NULL;
        }
        else if(current == last)
        {
            last = current->previus;
            last->next = NULL;
        }
        else
        {
            Node* right_old = current->next;

            current->previus->next = current->next;
            right_old->previus = current->previus;
        }

        delete current;
        amount--;
    }

    template<typename T>
    void List<T>::swap(const Iterator<T>& it_one, const Iterator<T>& it_two)
    {
        if(!it_one.current_node && !it_two.current_node)
            return;

        Node* pud_one = it_one.current_node;
        Node* pud_two = it_two.current_node;
        Node* tmp = it_one.current_node->next;

        if((it_one.current_node == first || it_two.current_node == first) && (it_one.current_node == last || it_two.current_node == last))
        {
            if(pud_one->previus)
            {
                pud_one = it_two.current_node;
                pud_two = it_one.current_node;
                tmp = pud_one->next;
            }

            pud_one->next = NULL;
            pud_one->previus = pud_two->previus;
            pud_one->previus->next = pud_one;

            pud_two->next = tmp;
            pud_two->previus = NULL;
            pud_two->next->previus = pud_two;

            tmp = first;
            first = last;
            last = tmp;

            return;
        }
        else if(it_one.current_node == first || it_two.current_node == first)
        {
            if(pud_one->previus)
            {
                pud_one = it_two.current_node;
                pud_two = it_one.current_node;
                tmp = pud_one->next;
            }

            pud_one->next = pud_two->next;
            pud_one->next->previus = pud_one;
            pud_one->previus = pud_two->previus;
            pud_one->previus->next = pud_one;

            pud_two->previus = NULL;
            pud_two->next = tmp;
            tmp->previus = pud_two;

            first = pud_two;

            return;
        }
        else if(it_one.current_node == last || it_two.current_node == last)
        {
            if(pud_two->next)
            {
                pud_two = it_one.current_node;
                pud_one = it_two.current_node;
            }

            tmp = pud_two->previus;

            pud_two->previus = pud_one->previus;
            pud_two->previus->next = pud_two;
            pud_two->next = pud_one->next;
            pud_two->next->previus = pud_two;

            pud_one->previus = tmp;
            pud_one->previus->next = pud_one;
            pud_one->next = NULL;

            last = pud_one;

            return;
        }

        pud_one = it_one.current_node->previus;
        pud_two = it_one.current_node->next;

        it_one.current_node->previus = it_two.current_node->previus;
        it_one.current_node->previus->next = it_one.current_node;
        it_one.current_node->next = it_two.current_node->next;
        it_one.current_node->next->previus = it_one.current_node;

        it_two.current_node->previus = pud_one;
        pud_one->next = it_two.current_node;
        it_two.current_node->next = pud_two;
        pud_two->previus = it_two.current_node;
    }

    template<typename T>
    void List<T>::copy(const List& in)
    {
        Node* current = in.first;

        for(uint32_t i = 0; i < in.size(); i++)
        {
            insertBack(current->object);
            current = current->next;
        }
    }
}

#endif // LIST_H


