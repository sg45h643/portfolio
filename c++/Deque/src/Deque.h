#ifndef DEQUE_H
#define DEQUE_H

#include <stdint.h>
#include <assert.h>

namespace tango
{
    template<typename T>
    class Deque;
}

#include "AbstractDeque.h"

#include "Iterator.h"
#include "ConstIterator.h"

#define _block_size 10
#define _base_index_size 20

namespace tango
{
    template<typename T>
    class Deque:
        public AbstractDeque<T>
    {
        public:
            friend class AbstractIterator<T>;
            friend class Iterator<T>;
            friend class ConstIterator<T>;

        public:
            Deque();
            Deque(size_t n, const T& value);
            Deque(Deque<T>& in);
            virtual ~Deque();

            Deque<T>& operator=(const Deque<T>& in);

            Iterator<T> begin();
            const ConstIterator<T> cbegin() const;
            Iterator<T> finish();
            const ConstIterator<T> cfinish() const;
            Iterator<T> end();
            const ConstIterator<T> cend() const;

            size_t size() const;
            void resize(size_t n);
            bool empty() const;
            void shrink_to_fit();

            T& operator[](uint32_t key);
            const T& operator[](uint32_t key) const;
            T& at(uint32_t key);
            const T& at(uint32_t key) const;
            T& front() const;
            T& back() const;

            void assign(size_t n, const T& value);
            void push_back(const T& value);
            void push_front(const T& value);
            void pop_back();
            void pop_front();
            void insert(Iterator<T> it, const T& value);
            void erase(Iterator<T> it);
            void swap(Deque<T>& in);
            void clear();

        private:
            T& search(uint32_t key) const;

        private:
            T** index;
            uint32_t index_size;
            uint32_t left_position, right_position;
            T* left, *right;
            uint32_t first, last;
            uint32_t deque_size;

            T** reserve_blocks;
            uint32_t rb_cnt;
    };

    template<typename T>
    Deque<T>::Deque():
        index(new T*[_base_index_size]),
        index_size(_base_index_size),
        left_position(_base_index_size / 2 - 1),
        right_position(_base_index_size / 2 - 1),
        first(0),
        last(0),
        deque_size(0),
        reserve_blocks(new T*[_base_index_size]),
        rb_cnt(0)
    {
        index[left_position] = new T[_block_size];

        left = index[left_position];
        right = index[left_position];
    }

    template<typename T>
    Deque<T>::Deque(size_t n, const T& value):
        index(new T*[_base_index_size]),
        index_size(_base_index_size),
        left_position(_base_index_size / 2 - 1),
        right_position(_base_index_size / 2 - 1),
        first(0),
        last(0),
        deque_size(0),
        reserve_blocks(new T*[_base_index_size]),
        rb_cnt(0)
    {
        index[left_position] = new T[_block_size];
        left = index[left_position];
        right = index[left_position];

        for(uint32_t i = 0; i < n; i++)
            push_back(value);
    }

    template<typename T>
    Deque<T>::Deque(Deque<T>& in):
        index(new T*[_base_index_size]),
        index_size(_base_index_size),
        left_position(_base_index_size / 2 - 1),
        right_position(_base_index_size / 2 - 1),
        first(0),
        last(0),
        deque_size(0),
        reserve_blocks(new T*[_base_index_size]),
        rb_cnt(0)
    {
        index[left_position] = new T[_block_size];
        left = index[left_position];
        right = index[left_position];

        for(uint32_t i = 0; i < in.size(); i++)
            push_back(in[i]);

        assert(in.size() == size());
    }

    template<typename T>
    Deque<T>::~Deque()
    {
        uint32_t i;

        for(i = left_position; i <= right_position; i++)
            delete[] index[i];

        delete[] index;

        for(i = 0; i < rb_cnt; i++)
            delete[] reserve_blocks[i];

        delete[] reserve_blocks;
    }

    template<typename T>
    Deque<T>& Deque<T>::operator=(const Deque<T>& in)
    {
        clear();

        for(uint32_t i = 0; i < in.size(); i++)
            push_back(in[i]);

        return *this;
    }

    template<typename T>
    Iterator<T> Deque<T>::begin()
    {
        return Iterator<T>(this, left, left_position, first + 1);
    }

    template<typename T>
    const ConstIterator<T> Deque<T>::cbegin() const
    {
        return ConstIterator<T>(this, left, left_position, first + 1);
    }

    template<typename T>
    Iterator<T> Deque<T>::finish()
    {
        return Iterator<T>(this, right, right_position, last);
    }

    template<typename T>
    const ConstIterator<T> Deque<T>::cfinish() const
    {
        return ConstIterator<T>(this, right, right_position, last);
    }

    template<typename T>
    Iterator<T> Deque<T>::end()
    {
        return Iterator<T>(this, NULL, right_position, last);
    }

    template<typename T>
    const ConstIterator<T> Deque<T>::cend() const
    {
        return ConstIterator<T>(this, NULL, right_position, last);
    }

    template<typename T>
    size_t Deque<T>::size() const
    {
        return deque_size;
    }

    template<typename T>
    void Deque<T>::resize(size_t n)
    {
        if(!n)
            clear();

        T some_var;
        uint32_t range;

        if(deque_size < n)
        {
            range = n - deque_size;

            for(uint32_t i = 0; i < range; i++)
                push_back(some_var);
        }
        else
        {
            range = deque_size - n;

            for(uint32_t i = 0; i < range; i++)
                pop_back();
        }
    }

    template<typename T>
    bool Deque<T>::empty() const
    {
        return deque_size;
    }

    template<typename T>
    void Deque<T>::shrink_to_fit()
    {
        for(int i = 0; i < rb_cnt; i++)
            delete[] reserve_blocks[i];

        rb_cnt = 0;
    }

    template<typename T>
    T& Deque<T>::operator[](uint32_t key)
    {
        assert(deque_size);

        return search(key);
    }

    template<typename T>
    const T& Deque<T>::operator[](uint32_t key) const
    {
        assert(deque_size);

        return search(key);
    }

    template<typename T>
    T& Deque<T>::at(uint32_t key)
    {
        assert(deque_size);

        return search(key);
    }

    template<typename T>
    const T& Deque<T>::at(uint32_t key) const
    {
        assert(deque_size);

        return search(key);
    }

    template<typename T>
    T& Deque<T>::front() const
    {
        assert(deque_size);

        return left[first];
    }

    template<typename T>
    T& Deque<T>::back() const
    {
        assert(deque_size);

        if(last == 0)
            return left[_block_size - 1];

        return right[last - 1];
    }

    template<typename T>
    void Deque<T>::assign(size_t n, const T& value)
    {
        clear();

        for(uint32_t i = 0; i < n; i++)
            push_back(value);
    }

    template<typename T>
    void Deque<T>::push_back(const T& value)
    {
        if(last == _block_size)
        {
            right_position++;

            if(right_position == index_size)
            {
                const uint32_t tmp_index_size = index_size + _base_index_size;
                T** tmp_index = new T*[tmp_index_size];

                for(uint32_t i = left_position; i < right_position; i++)
                    tmp_index[i] = index[i];

                delete[] index;
                index = tmp_index;
                index_size = tmp_index_size;
            }

            if(rb_cnt)
            {
                index[right_position] = reserve_blocks[rb_cnt - 1];
                rb_cnt--;
            }
            else
            {
                index[right_position] = new T[_block_size];
            }

            right = index[right_position];
            last = 0;
        }

        right[last] = value;
        last++;
        deque_size++;
    }

    template<typename T>
    void Deque<T>::push_front(const T& value)
    {
        if(!first)
        {
            left_position--;

            if(!left_position)
            {
                const uint32_t tmp_index_size = index_size + _base_index_size;
                T** tmp_index = new T*[tmp_index_size];

                for(uint32_t i = 1; i <= right_position; i++)
                    tmp_index[i + _base_index_size] = index[i];

                left_position = _base_index_size;

                delete[] index;
                index = tmp_index;
                index_size = tmp_index_size;
                right_position += _base_index_size;
            }


            if(rb_cnt)
            {
                index[left_position] = reserve_blocks[rb_cnt - 1];
                rb_cnt--;
            }
            else
                index[left_position] = new T[_block_size];

            left = index[left_position];
            first = _block_size - 1;
        }
        else
            first--;

        left[first] = value;
        deque_size++;
    }

    template<typename T>
    void Deque<T>::pop_back()
    {
        if(deque_size)
        {
            if(!last)
            {
                if(rb_cnt < _base_index_size)
                {
                    reserve_blocks[rb_cnt] = right;
                    rb_cnt++;
                }
                else
                    delete[] right;

                right_position--;
                right = index[right_position];
                last = _block_size - 1;
            }
            else
                last--;

            deque_size--;
        }
    }

    template<typename T>
    void Deque<T>::pop_front()
    {
        if(deque_size)
        {
            if(first == _block_size - 1)
            {
                if(rb_cnt < _base_index_size)
                {
                    reserve_blocks[rb_cnt] = left;
                    rb_cnt++;
                }
                else
                    delete[] left;

                left_position++;
                left = index[left_position];
                first = 0;
            }
            else
                first++;

            deque_size--;
        }
    }

    template<typename T>
    void Deque<T>::insert(Iterator<T> it, const T& value)
    {
        if(it.deque != this)
            return;

        if(left_position <= it.n_tab && it.n_tab <= right_position)
        {
            if(!it.tab)
            {
                push_back(value);
                return;
            }

            uint32_t x, y;
            push_back(right[last - 1]);

            uint32_t j = last - 2;

            for(uint32_t i = right_position; it.n_tab < i; i--)
            {
                while(0 < j)
                {
                    index[i][j] = index[i][j - 1];
                    j--;
                }

                index[i][0] = index[i - 1][_block_size - 1];
                j = _block_size - 1;
            }

            if(it.n_tab == right_position)
                j = last - 2;
            else
                j = _block_size - 1;

            while(it.offset - 1 < j)
            {
                index[it.n_tab][j] = index[it.n_tab][j - 1];
                j--;
            }

            index[it.n_tab][it.offset - 1] = value;
        }
    }

    template<typename T>
    void Deque<T>::erase(Iterator<T> it)
    {
        if(it.deque != this || !it.tab)
            return;

        uint32_t x = it.n_tab;
        uint32_t y = it.offset;

        if(x < left_position || right_position < x)
            return;

        if(x == left_position && y - 1 == first)
        {
            pop_front();
            return;
        }

        if(x == right_position)
        {
            for(uint32_t i = y - 1; i < last - 1; i++)
                index[x][i] = index[x][i + 1];

            pop_back();
            return;
        }
        else
        {
            for(uint32_t i = y - 1; i < _block_size - 2; i++)
                index[x][i] = index[x][i + 1];

            x++;
        }

        do
        {
            index[x - 1][_block_size - 1] = index[x][0];

            for(uint32_t i = 0; i < _block_size - 2; i++)
                index[x][i] = index[x][i + 1];

            x++;
        }
        while(x <= right_position);

        pop_back();
    }

    template<typename T>
    void Deque<T>::swap(Deque<T>& in)
    {
        Deque<T> tmp_deq(in);
        in.clear();

        for(uint32_t i = 0; i < deque_size; i++)
            in.push_back(at(i));

        clear();

        for(uint32_t i = 0; i < tmp_deq.size(); i++)
            push_back(tmp_deq.at(i));
    }

    template<typename T>
    void Deque<T>::clear()
    {
        if(deque_size <= _block_size)
        {
            if(left != right)
            {
                delete[] left;
                left = right;
                left_position = right_position;
            }

            deque_size = 0;
            first = 0;
            last = 0;

            return;
        }

        for(uint32_t i = left_position; i <= right_position; i++)
        {
            if(rb_cnt < _base_index_size)
            {
                reserve_blocks[rb_cnt] = index[i];
                rb_cnt++;
            }
            else
                delete[] index[i];
        }

        delete[] index;
        index = new T*[_base_index_size];
        index_size = _base_index_size;

        uint32_t index_section = _base_index_size / 2;

        left_position = index_section - 1;
        right_position = index_section - 1;

        index[left_position] = new T[_block_size];

        left = index[left_position];
        right = index[left_position];

        deque_size = 0;

        first = 0;
        last = 0;
    }

    template<typename T>
    T& Deque<T>::search(uint32_t key) const
    {
        uint32_t first_block = _block_size - first;

        if(key < first_block)
            return left[first + key];

        key -= first_block;

        uint32_t jump = key / _block_size + 1;
        uint32_t rest = key % _block_size;

        return index[left_position + jump][rest];
    }
}

#endif // DEQUE_H
