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
        
        typedef value_type& reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

        typedef value_type*       iterator;
        typedef const value_type* const_iterator;
        typedef value_type* reverse_iterator;
        typedef const value_type* const_reverse_iterator;
    protected:
        typedef Alloc data_allocator;
        iterator _start;
        iterator _finish;
        iterator _end_of_storage;

    private:
    // helper function
        void deallocate()
        {
            if (_start)
                data_allocator::deallocate(_start, _end_of_storage - _start);
        }

        void destroy_and_deallocate()
        {
            data_allocator::destroy(_start, _finish);
            deallocate();
        }

        void fill_initialize(size_type n, const value_type& value)
        {
            _start = allocate_n_fill(n, value);
            _finish = _end_of_storage = _start + n;
        }
        iterator allocate_n_fill(size_type n, const value_type& value)
        {
            iterator result = data_allocator::allocate(n);
            uninitialized_fill_n(result, n, value);
            return result;
        }
        
        // reallocate
        void      reallocate_insert(iterator pos, const value_type& value);
    public:
        //resue print function
        void print() const
        {
            for (auto it = _start; it != _finish; it++)
            {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
        // 构造、复制、移动、析构函数
    public:
        // construct, copy, move, destruct
        vector()
        {
            _start = _finish = _end_of_storage = nullptr;
        }
        vector(size_type n)
        {
            fill_initialize(n, value_type());
        }
        vector(size_type n, value_type value)
        {
            fill_initialize(n, value);
        }
        vector(const vector& other)
        {
            size_type n = other.capacity();
            _start = data_allocator::allocate(n);
            _finish = uninitialized_copy(other._start, other._finish, _start);
            _end_of_storage = _finish;
        }
        vector(vector&& other) noexcept
        {
            printf("moved constructor\n");
            if (this != &other)
            {
                _start = other._start;
                _finish = other._finish;
                _end_of_storage = other._end_of_storage;

                other._start = nullptr;
                other._finish = nullptr;
                other._end_of_storage = nullptr;
            }
        }
        ~vector()
        {
            destroy_and_deallocate();
        }
        // to do 
        vector& operator=(const vector& other)
        {
            // optimize case
            // compare size of this and other
            
            if (this != &other)
            {
                if (this->capacity() >= other.size())
                {
                    data_allocator::destroy(_start, _finish);
                    uninitialized_copy(other._start, other._finish, _start);
                    _finish = _start + other.size();
                }
                else
                {
                    destroy_and_deallocate();
                    _start = data_allocator::allocate(_start, other.capacity());
                    uninitialized_copy(other._start, other._finish, _start);
                    _finish =  _start + other.size();
                    _end_of_storage = _start + other.capacity();

                }
            }

            return *this;
        }

        vector& operator=(vector&& other) noexcept
        {
            printf("Moved\n");

            if (this != &other)
            {
                destroy_and_deallocate();

                _start = other._start;
                _finish = other._finish;
                _end_of_storage = other._end_of_storage;

                other._start = nullptr;
                other._finish = nullptr;
                other._end_of_storage = nullptr;
            }

            return *this;
        }
     
        // iterator operation
    public:
        iterator begin() 
        { 
            return _start; 
        }
        iterator end() 
        { 
            return _finish; 
        }
        iterator cbegin() const 
        { 
            return _start; 
        }
        iterator cend() const 
        {
            return _finish;
        }

        // container operation
    public:
        size_type size() 
        { 
            return static_cast<size_type>(end() - begin()); 
        }
        size_type capacity() const
        {
            return (size_type)(_end_of_storage - _start);
        }
        bool empty() const
        {
            return _start == _finish;
        }

        // element Access
    public:
        void push_back(const value_type& x)
        {
            if (_finish != _end_of_storage)
            {
                MessySTL::construct(_finish, x);
                ++_finish;
            }
            else
            {
                reallocate_insert(end(), x);
            }
            
        }

    };
    template<class T, class Alloc>
    inline void vector<T, Alloc>::reallocate_insert(iterator pos, const value_type& value)
    {
        // needed by insert function
        // to do
        // implement copy and move utility function
        if (_finish != _end_of_storage)
        {
            MessySTL::construct(_finish, value);
            ++_finish;
        }
        else
        {
            size_type old_size = size();
            size_type new_size = (old_size == 0) ? 1 : 2 * old_size;

            iterator _new_start = data_allocator::allocate(new_size);
            iterator _new_end = _new_start;

            try
            {
                _new_end = uninitialized_copy(_start, _finish, _new_start);
                construct(_new_end, value);
                ++_new_end;
                
                // needed by insert
                _new_end = uninitialized_copy(pos, _finish, _new_end);
            }
            catch (...)
            {
                data_allocator::deallocate(_new_start, new_size);
                throw;
            }
            destroy_and_deallocate();
            _start = _new_start;
            _finish = _new_end;
            _end_of_storage = _start + new_size;
        }
    }
}

