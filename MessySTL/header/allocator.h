#pragma once
#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <new>
#include "construct.h"
namespace MessySTL
{
    template<class T>
    class allocator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

    public:
        // static because it serves for class not instance.
        static T* allocate();
        static T* allocate(size_type n);

        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_type n);

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void construct(T* ptr, T&& value);

        static void destroy(T* ptr);
        static void destroy(T* first, T* last);
      
    };
   

    template<class T>
    inline T* allocator<T>::allocate()
    {
        return static_cast<T*> (operator new(sizeof(T)));
    }

    template<class T>
    inline T* allocator<T>::allocate(size_type num_of_obj)
    {
        if (num_of_obj == 0)
        {
            return nullptr;
        }
        return static_cast<T*>(operator new(num_of_obj * sizeof(T)));
    }

    template<class T>
    inline void allocator<T>::deallocate(T* ptr)
    {
        if (ptr == nullptr)
        {
            return;
        }
        operator delete(ptr);
    }

    template<class T>
    inline void allocator<T>::deallocate(T* ptr, size_type n)
    {
        if (ptr == nullptr || n == 0)
        {
            return;
        }
        operator delete(ptr);
    }

    template<class T>
    inline void allocator<T>::construct(T* ptr)
    {
        MessySTL::construct(ptr);
    }

    template<class T>
    inline void allocator<T>::construct(T* ptr, const T& value)
    {
        MessySTL::construct(ptr, value);
    }

    template<class T>
    inline void allocator<T>::construct(T* ptr, T&& value)
    {
    }
    template<class T>
    inline void allocator<T>::destroy(T* ptr)
    {
        MessySTL::destroy(ptr);
    }
    template<class T>
    inline void allocator<T>::destroy(T* first, T* last)
    {
        MessySTL::destroy(first, last);
    }
}
#endif // !ALLOCATOR_H_
