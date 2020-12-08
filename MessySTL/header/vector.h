#pragma once

#include "pool_alloc.h"
#include "uninitialized_function.h"
namespace MessySTL
{
    template<class T, class Alloc = pool_alloc<T>>
    class vector
    {
    public:
        typedef T           value_type;
        typedef value_type* pointer;
        typedef value_type* iterator;
        typedef value_type& reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

    protected:
        typedef Alloc data_allocator;
        iterator _start;
        iterator _finish;
        iterator _end_of_storage;

        void insert_aux(iterator position, const T& x);
        void deallocate()
        {
            if (_start)
                data_allocator::deallocate(_start, _end_of_storage - _start);
        }
    public:
        vector();
        vector(size_type n);
        iterator begin() { return _start;  }
        iterator end() { return _finish; }
        size_type size() { return static_cast<size_type>(end() - begin()); }
        size_type capacity() const
        {
            return (size_type)(_end_of_storage - _start);
        }
        bool empty() const
        {
            return _start == _finish;
        }
        void push_back(const value_type& x)
        {

        }

    };
    template<class T, class Alloc>
    inline vector<T, Alloc>::vector()
    {
        _start = _finish = _end_of_storage = nullptr;
    }
    template<class T, class Alloc>
    inline vector<T, Alloc>::vector(size_type n)
    {
        _start = data_allocator::allocate(n);
        _finish = _end_of_storage = uninitialized_fill_n(_start, n, value_type());;
    }
}

