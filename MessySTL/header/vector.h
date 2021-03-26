#pragma once

#include "pool_alloc.h"
#include "allocator.h"
#include "uninitialized_function.h"
#include "exceptdef.h"

namespace MessySTL
{
    template<class T, class Alloc = allocator<T>>
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
        
        // to do
        /*typedef value_type*         reverse_iterator;
        typedef const value_type*   const_reverse_iterator;*/
    protected:
        typedef Alloc               data_allocator;
        iterator _begin;
        iterator _end;
        iterator _capacity;

    protected:
        // helper function
        void partial_dellocate(iterator first, size_type n)
        {
            data_allocator::deallocate(first, n);
        }
        void deallocate()
        {
            if (_begin)
                data_allocator::deallocate(_begin, _capacity - _begin);
        }

        void destroy_and_deallocate(iterator first, iterator last)
        {
            data_allocator::destroy(first, last);
            deallocate();
        }

        void fill_initialize(size_type n, const value_type& value)
        {
            _begin = allocate_n_fill(n, value);
            _end = _capacity = _begin + n;
        }

        iterator allocate_n_fill(size_type n, const value_type& value)
        {
            iterator result = data_allocator::allocate(n);
            uninitialized_fill_n(result, n, value);
            return result;
        }
        
        // reallocate
        void reallocate_insert(iterator pos, const value_type& value);
        void reallocate_fill(size_type n, const value_type& value);
        void reallocate_emplace(iterator pos, T&& value);
        template<class ...Args>
        void reallocate_emplace(iterator pos, Args&& ...args);
    public:
        //resue print function
        void print() const
        {
            for (auto it = _begin; it != _end; it++)
            {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
    public:
        // constructor, destructor, copy operator, move operator 
        vector()
        {
            _begin = _end = _capacity = nullptr;
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
            _begin = data_allocator::allocate(n);
            _end = uninitialized_copy(other._begin, other._end, _begin);
            _capacity = _end;
        }
        vector(vector&& other) noexcept
        {
            printf("moved constructor\n");
            if (this != &other)
            {
                _begin = other._begin;
                _end = other._end;
                _capacity = other._capacity;

                other._begin = nullptr;
                other._end = nullptr;
                other._capacity = nullptr;
            }
           
        }
        ~vector()
        {
            destroy_and_deallocate(_begin, _end);
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
                    data_allocator::destroy(_begin, _end);
                    uninitialized_copy(other._begin, other._end, _begin);
                    _end = _begin + other.size();
                }
                else
                {
                    destroy_and_deallocate(_begin, _end);
                    _begin = data_allocator::allocate(_begin, other.capacity());
                    uninitialized_copy(other._begin, other._end, _begin);
                    _end =  _begin + other.size();
                    _capacity = _begin + other.capacity();

                }
            }

            return *this;
        }

        vector& operator=(vector&& other) noexcept
        {
            printf("Moved\n");

            if (this != &other)
            {
                destroy_and_deallocate(_begin, _end);

                _begin = other._begin;
                _end = other._end;
                _capacity = other._capacity;

                other._begin = nullptr;
                other._end = nullptr;
                other._capacity = nullptr;
            }

            return *this;
        }
     
        // ---------- iterator ---------------
    public:
        iterator begin() noexcept 
        { 
            return _begin; 
        }
        iterator end() noexcept
        { 
            return _end;  
        }
        iterator cbegin() const noexcept 
        { 
            return _begin; 
        }
        iterator cend() const noexcept
        { 
            return _end; 
        }

        // ---------- capacity ---------------
    public:
        size_type size() const noexcept
        { 
            return size_type(_end - _begin); 
        }
      
        size_type capacity() const noexcept
        { 
            return size_type(_capacity - _begin); 
        }
        bool empty() const noexcept
        { 
            return _begin == _end; 
        }

        // ---------- element access ---------------
        reference operator[](size_type n)
        {
            MESSY_ASSERT(n < size());
            return *(_begin + n);
        }

        const_reference operator[](size_type n) const
        {
            MESSY_ASSERT(n < size());
            return *(_begin + n);
        }

        reference at(size_type n)
        {
            THROW_OUT_OF_RANGE_IF((n > size()), "vector<T>::at() subscript out of range");
            return (*this)[n];
        }

        const_reference at(size_type n) const
        {
            THROW_OUT_OF_RANGE_IF((n > size()), "vector<T>::at() subscript out of range");
            printf("const at is called\n");
            return (*this)[n];
        }

        reference front()
        {
            MESSY_ASSERT(!empty());
            return *_begin;
        }

        const_reference front() const
        {
            MESSY_ASSERT(!empty());
            printf("const front is called\n");
            return *_begin;
        }
        
        /// <summary>
        /// return the last element in the vector
        /// </summary>
        /// <returns></returns>
        reference back()
        {
            MESSY_ASSERT(!empty());
            return *(_end - 1);
        }
        
        const_reference back() const
        {
            MESSY_ASSERT(!empty());
            printf("const back is called\n");
            return *(_end - 1);
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
            return _begin;
        }

        const_pointer data() const noexcept
        {
            MESSY_ASSERT(!empty());
            return _begin;
        }

        // ---------- Modifiers ---------------
    public:
        void assign(size_type n, const value_type& val);
        void assign(iterator first, iterator last);
        void clear();
        void push_back(const value_type& x);
        void push_back(value_type&& x);
        
        void pop_back();
        void resize(size_type n);
        void resize(size_type n, const value_type& val);
        iterator erase(iterator first, iterator last);
        iterator erase(iterator position);
      

        void insert(iterator position, const value_type& val);
        
        void insert(iterator position, size_type n, const value_type& value);
       
        template <class... Args>
        iterator emplace(const_iterator position, Args&&... args);
        template <class... Args>
        void emplace_back(Args&&... args);


        // comparison
        bool operator==(const vector& other)
        {
            if (this->size() == other.size())
            {
                for (auto it = this->begin(), it2 = other.begin(); it != this->end(); it++)
                {
                    if (*it != *it2)
                        return false;

                }
                return true;
            }
            return false;
        }
       

    };
    template<class T, class Alloc>
    inline void vector<T, Alloc>::reallocate_insert(iterator pos, const value_type& value)
    {
        
        if (_end != _capacity)
        {
            // if pos == _finish, last < first while using copy_backward
            // handle it here
            if (pos == _end)
            {
                data_allocator::construct(_end, value);
                ++_end;
            }
            else
            {
                data_allocator::construct(_end, *(_end - 1));
                ++_end;

                T value_copy = value;
                //_finish + 2 may failed if _finish + 1 = _end_of_storage
                MessySTL::copy_backward(pos, _end - 2, _end - 1);
                *pos = value_copy;
            }
            
        }
        else
        {
            const size_type old_size = size();
            const size_type new_size = (old_size == 0) ? 1 : 2 * old_size;

            iterator _new_begin = data_allocator::allocate(new_size);
            iterator _new_end = _new_begin;

            try
            {
                _new_end = uninitialized_copy(_begin, pos, _new_begin);
                construct(_new_end, value);
                ++_new_end;
                
                // needed by insert
                _new_end = uninitialized_copy(pos, _end, _new_end);
            }
            catch (...)
            {
                data_allocator::deallocate(_new_begin, new_size);
                throw;
            }
            destroy_and_deallocate(_begin, _end);
            _begin = _new_begin;
            _end = _new_end;
            _capacity = _begin + new_size;
        }
    }

    template<class T, class Alloc>
    inline void vector<T, Alloc>::reallocate_fill(size_type n, const value_type& value)
    {
        size_type old_size = size();
        size_type new_size = n;

        iterator _new_begin = data_allocator::allocate(new_size);
        iterator _new_end = _new_begin;

        try
        {
            _new_end = uninitialized_copy(_begin, _end, _new_begin);
            _new_end = uninitialized_fill_n(_new_end, new_size - old_size, value);
        }
        catch (...)
        {
            data_allocator::deallocate(_new_begin, new_size);
            throw;
        }
        destroy_and_deallocate(_begin, _end);
        _begin = _new_begin;
        _end = _new_end;
        _capacity = _begin + new_size;
    }

    template<class T, class Alloc>
    inline void vector<T, Alloc>::reallocate_emplace(iterator pos, T&& value)
    {
        size_type old_size = size();
        size_type new_size = (old_size == 0) ? 1 : 2 * old_size;

        iterator _new_begin = data_allocator::allocate(new_size);
        iterator _new_end = _new_begin;

        try
        {
            _new_end = uninitialized_move(_begin, pos, _new_begin);
            data_allocator::construct(_new_end, MessySTL::forward<T>(value));
            ++_new_end;
            _new_end = uninitialized_move(pos, _end, _new_end);
        }
        catch (...)
        {
            data_allocator::deallocate(_new_begin, new_size);
            throw;
        }
        destroy_and_deallocate(_begin, _end);
        _begin = _new_begin;
        _end = _new_end;
        _capacity = _begin + new_size;

    }

    template<class T, class Alloc>
    template<class ...Args>
    inline void vector<T, Alloc>::reallocate_emplace(iterator pos, Args&& ...args)
    {
        size_type old_size = size();
        size_type new_size = (old_size == 0) ? 1 : 2 * old_size;

        iterator _new_begin = data_allocator::allocate(new_size);
        iterator _new_end = _new_begin;

        try
        {
            _new_end = uninitialized_move(_begin, pos, _new_begin);
            data_allocator::construct(_new_end, MessySTL::forward<Args>(args)...);
            ++_new_end;
            _new_end = uninitialized_move(pos, _end, _new_end);
        }
        catch (...)
        {
            data_allocator::deallocate(_new_begin, new_size);
            throw;
        }
        destroy_and_deallocate(_begin, _end);
        _begin = _new_begin;
        _end = _new_end;
        _capacity = _begin + new_size;
    }

    // to do
    template<class T, class Alloc>
    void vector<T, Alloc>::assign(size_type n, const value_type& val)
    {
        if (n > capacity())
        {
            reallocate_fill(n, val);
        }
        else
        {
            data_allocator::destroy(_begin, _end);
            _end = uninitialized_fill_n(_begin, n, val);
        }

    }
    template<class T, class Alloc>
    void vector<T, Alloc>::assign(iterator first, iterator last)
    {
        size_type new_size = last - first;
        if (new_size > capacity())
        {
            iterator _new_begin = data_allocator::allocate(new_size);
            iterator _new_end = _new_begin;
            try 
            {
                _new_end = uninitialized_copy(first, last, _new_begin);
            }
            catch (...)
            {
                data_allocator::deallocate(_new_begin, new_size);
                throw;
            }
            destroy_and_deallocate(_begin, _end);
            _begin = _new_begin;
            _end = _new_end;
            _capacity = _begin + new_size;
        }
        else
        {
            data_allocator::destroy(_begin, _end);
            _end = uninitialized_copy(first, last, _begin);

        }
    }
    template<class T, class Alloc>
    void MessySTL::vector<T, Alloc>::clear()
    {
        data_allocator::destroy(_begin, _end);
        _end = _begin;
    }
    template<class T, class Alloc>
    void MessySTL::vector<T, Alloc>::push_back(const value_type& x)
    {
        if (_end != _capacity)
        {
            MessySTL::construct(_end, x);
            ++_end;
        }
        else
        {
            reallocate_insert(end(), x);
        }
    }
    template<class T, class Alloc>
    void vector<T, Alloc>::push_back(value_type&& x)
    {
        emplace_back(MessySTL::move(x));
    }
    template<class T, class Alloc>
    void vector<T, Alloc>::pop_back()
    {
        --_end;
        destroy(_end);
    }
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
    {
        iterator i = copy(last, _end, first);
        destroy(i, _end);
        _end = _end - (last - first);
        return first;
    }
    template<class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
    {
        copy(position + 1, _end, position);
        --_end;
        destroy(_end);
        return position;
    }
    template<class T, class Alloc>
    void vector<T, Alloc>::resize(size_type n)
    {
        resize(n, T());
    }

    template<class T, class Alloc>
    void vector<T, Alloc>::resize(size_type n, const value_type& val)
    {
        if (n <= capacity())
        {
            if (n < size())
            {
                erase(_begin + n, _end);
            }
            else if(n > size())
            {
                insert(_end, n - size(), val);
            }
        }
        else
        {
            reallocate_fill(n, val);
        }
        
    }
    template<class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, const value_type& val)
    {
        reallocate_insert(position, val);
    }
    

    template<class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, size_type n, const value_type& value)
    {
        if (n != 0)
        {
            MESSY_ASSERT(position <= end() && position >= begin());
            // if backup storage greater than new elements
            size_type back_up = _capacity - _end;
            if (back_up >= n)
            {
                const size_type num_elems_after = _end - position;
                iterator _old_end = _end;
                if (num_elems_after > n)
                {
                    iterator _new_end = uninitialized_copy(position, position + n, _end);
                    copy_backward(position, _end, _new_end);
                    fill_n(position, n, value);
                    _end = _new_end;
                }
                else
                {
                    //expand space in backup because there is not enough space
                    uninitialized_fill_n(_end, n - num_elems_after, value);
                    _end += n - num_elems_after;
                    uninitialized_copy(position, _old_end, _end);
                    _end += num_elems_after;
                    fill_n(position, n, value);
                }

            }
            else
            {
                const size_type old_size = capacity();
                const size_type new_size = old_size == 0 ? 1 : old_size * 2;
                iterator _new_begin = data_allocator::allocate(new_size);
                iterator _new_end = _new_begin;

                try
                {
                    _new_end = uninitialized_copy(_begin, position, _new_begin);
                    _new_end = uninitialized_fill_n(_new_end, n, value);
                    _new_end = uninitialized_copy(position, _end, _new_end);
                }
                catch (...)
                {
                    // commit or rollback
                    data_allocator::deallocate(_new_begin, new_size);
                    throw;
                }

                destroy_and_deallocate(_begin, _end);
                _begin = _new_begin;
                _end = _new_end;
                _capacity = _begin + new_size;
            }
           
        }
    }

    // to do
    template<class T, class Alloc>
    template<class ...Args>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(const_iterator position, Args && ...args)
    {
        MESSY_ASSERT(position >= begin() && position <= end());
        iterator pos = const_cast<iterator>(position);
        const size_type n = pos - _begin;
        if (_end != _capacity && pos == end())
        {
            data_allocator::construct(&*_end, MessySTL::forward<Args>(args)...);
            ++_end;
        }
        else if (_end != _capacity)
        {
            data_allocator::construct(&*_end, *(_end - 1));
            ++_end;
            MessySTL::copy_backward(pos, _end - 2, _end - 1);
            *pos = value_type(MessySTL::forward<Args>(args)...);
        }
        else
        {
            reallocate_emplace(pos, MessySTL::forward<Args>(args)...);
        }
        return begin() + n;
      
    }
    template<class T, class Alloc>
    template<class ...Args>
    void vector<T, Alloc>::emplace_back(Args && ...args)
    {
        if (_end < _capacity)
        {
            data_allocator::construct(_end, args...);
            ++_end;
        }
        else
        {
            reallocate_emplace(_end, args...);
        }
    }
}

