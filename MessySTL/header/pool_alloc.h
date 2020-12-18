#pragma once

#include "alloc.h"
#include "construct.h"
namespace MessySTL
{
    template<class T>
    class pool_alloc
    {
    public:
        static T* allocate();
        static T* allocate(size_t n);
        static void deallocate(T* p);
        static void deallocate(T* p, size_t n);
       

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void construct(T* ptr, T&& value);

        static void destroy(T* ptr);
        static void destroy(T* first, T* last);
    };

    template<class T>
    inline T* pool_alloc<T>::allocate()
    {
        return static_cast<T*>(alloc::allocate(sizeof(T)));
    }

    /*
    * Take in a number of item
    * calculate the total bytes needed
    * and pass to allocate which takes byte
    */
    template<class T>
    inline T* pool_alloc<T>::allocate(size_t n)
    {
        return static_cast<T*>(alloc::allocate(n * sizeof(T)));
    }

    template<class T>
    inline void pool_alloc<T>::deallocate(T* p)
    {
        return alloc::deallocate(static_cast<void*>(p), sizeof(T));
    }

    template<class T>
    inline void pool_alloc<T>::deallocate(T* p, size_t n)
    {
        return alloc::deallocate(static_cast<void*>(p), sizeof(T) * n);
    }

    template<class T>
    inline void pool_alloc<T>::construct(T* ptr)
    {
        MessySTL::construct(ptr);
    }

    template<class T>
    inline void pool_alloc<T>::construct(T* ptr, const T& value)
    {
        MessySTL::construct(ptr, value);
    }

    template<class T>
    inline void pool_alloc<T>::construct(T* ptr, T&& value)
    {
    }
    template<class T>
    inline void pool_alloc<T>::destroy(T* ptr)
    {
        MessySTL::destroy(ptr);
    }
    template<class T>
    inline void pool_alloc<T>::destroy(T* first, T* last)
    {
        MessySTL::destroy(first, last);
    }
}