#pragma once

#include "pool_alloc.h"
#include "uninitialized_function.h"
#include "exceptdef.h"

namespace MessySTL
{
    template<class T, class Alloc = pool_alloc<T>>
    class vector
    {
    public:
        typedef T                   value_type;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef size_t              size_type;
        typedef ptrdiff_t           difference_type;

        typedef value_type*         iterator;
        typedef const value_type*   const_iterator;
        typedef value_type*         reverse_iterator;
        typedef const value_type*   const_reverse_iterator;
    protected:
        typedef Alloc               data_allocator;
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
        reference operator[](size_type n)
        {
            MESSY_ASSERT(n < size());
            return *(_start + n);
        }

        const_reference operator[](size_type n) const
        {
            MESSY_ASSERT(n < size());
            return *(_start + n);
        }

        reference at(size_type n)
        {
            THROW_OUT_OF_RANGE_IF((n > size()), "vector<T>::at() subscript out of range");
            return (*this)[n];
        }

        const_reference at(size_type n) const
        {
            THROW_OUT_OF_RANGE_IF((n > size()), "vector<T>::at() subscript out of range");
            return (*this)[n];
        }

        reference front()
        {
            MESSY_ASSERT(!empty());
            return *_start;
        }

        const_reference front() const
        {
            MESSY_ASSERT(!empty());
            return *_start;
        }
        
        /// <summary>
        /// return the last element in the vector
        /// </summary>
        /// <returns></returns>
        reference back()
        {
            MESSY_ASSERT(!empty());
            return *(_finish - 1);
        }
        
        const_reference back() const
        {
            MESSY_ASSERT(!empty());
            return *(_finish - 1);
        }

        /// <summary>
        /// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
        /// </summary>
        /// <returns>
        /// A pointer to the first element in the array used internally by the vector.
        /// If the vector object is const - qualified, the function returns a pointer to const value_type.
        /// Otherwise, it returns a pointer to value_type.
        /// </returns>
        pointer data() noexcept
        {
            MESSY_ASSERT(!empty());
            return *_start;
        }

        const_pointer data() const noexcept
        {
            MESSY_ASSERT(!empty());
            return *_start;
        }

    public:
        void push_back(const value_type& x);
        
        void pop_back();
      

        iterator erase(iterator first, iterator last);
        iterator erase(iterator position);
      

        void insert(const_iterator position, const value_type& val);
        
        void insert(iterator position, size_type n, const value_type& value);
       
        template <class... Args>
        iterator emplace(const_iterator position, Args&&... args);
       

    };
    template<class T, class Alloc>
    void vector<T, Alloc>::reallocate_insert(iterator pos, const value_type& value)
    {
        // needed by insert function
        // to do
        // implement copy and move utility function
        if (_finish != _end_of_storage)
        {
            construct(_finish, *(_finish - 1));
            ++_finish;

            //_finish + 2 may failed if _finish + 1 = _end_of_storage
            MessySTL::copy_backward(pos, _finish - 2, _finish - 1);
            *pos = value;
        }
        else
        {
            const size_type old_size = size();
            const size_type new_size = (old_size == 0) ? 1 : 2 * old_size;

            iterator _new_start = data_allocator::allocate(new_size);
            iterator _new_finish = _new_start;

            try
            {
                _new_finish = uninitialized_copy(_start, pos, _new_start);
                construct(_new_finish, value);
                ++_new_finish;
                
                // needed by insert
                _new_finish = uninitialized_copy(pos, _finish, _new_finish);
            }
            catch (...)
            {
                data_allocator::deallocate(_new_start, new_size);
                throw;
            }
            destroy_and_deallocate();
            _start = _new_start;
            _finish = _new_finish;
            _end_of_storage = _start + new_size;
        }
    }
    template<class T, class Alloc>
    void MessySTL::vector<T, Alloc>::push_back(const value_type& x)
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
    template<class T, class Alloc>
    void vector<T, Alloc>::pop_back()
    {
        --_finish;
        destroy(_finish);
    }
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
    {
        iterator i = copy(last, _finish, first);
        destroy(i, _finish);
        _finish = _finish - (last - first);
        return first;
    }
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
    {
        copy(position + 1, _finish, position);
        --_finish;
        destroy(_finish);
        return position;
    }

    // to do
    template<class T, class Alloc>
    void vector<T, Alloc>::insert(const_iterator position, const value_type& val)
    {
        reallocate_insert(position, val);
    }
    

    // to do
    template<class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, size_type n, const value_type& value)
    {
        if (n != 0)
        {
            MESSY_ASSERT(position < end() && position >= begin());
            // if backup storage greater than new elements
            size_type back_up = _end_of_storage - _finish;
            if (back_up >= n)
            {
                const size_type num_elems_after = _finish - position;
                iterator old_finish = _finish;
                if (num_elems_after > n)
                {
                    iterator _new_finish = uninitialized_copy(position, position + n, _finish);
                    copy_backward(position, _finish, _new_finish);
                    fill_n(position, n, value);
                    _finish = _new_finish;
                }
                else
                {
                    //expand space in backup because there is not enough space
                    uninitialized_fill_n(_finish, n - num_elems_after, value);
                    _finish += n - num_elems_after;
                    uninitialized_copy(position, old_finish, _finish);
                    _finish += num_elems_after;
                    fill_n(position, n, value);
                }

            }
            else
            {
                const size_type old_size = size();
                const size_type new_size = old_size == 0 ? 1 : old_size * 2;
                iterator new_start = data_allocator::allocate(new_size);
                iterator new_finish = new_start;

                try
                {
                    new_finish = uninitialized_copy(_start, position, new_start);
                    new_finish = uninitialized_fill_n(new_finish, n, value);
                    new_finish = uninitialized_copy(position, _finish, new_finish);
                }
                catch (...)
                {
                    // commit or rollback
                    data_allocator::deallocate(_new_start, new_size);
                    throw;
                }

                destroy_and_deallocate(_start, _finish);
                _start = new_start;
                _finish = new_finish;
                _end_of_storage = _start + new_size;
            }
           
        }
    }

    // to do
    template<class T, class Alloc>
    template<class ...Args>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(const_iterator position, Args && ...args)
    {
    }
}

