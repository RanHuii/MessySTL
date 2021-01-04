#pragma once
#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include <new>
#include "type_traits.h"
#include "iterator_base.h"
#include "util.h"
/*
* This class only contains construct and destroy function
* It has different versions of construct and destroy function for different cases 
* We use type trait to optimize our choice
* 
*/

namespace MessySTL {

    template<class T>
    void construct(T* p)
    {
        new(p)T();
    }
    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T1">class type</typeparam>
    /// <typeparam name="T2">parameter type</typeparam>
    /// <param name="p">pointer of the allocated memory</param>
    /// <param name="value"></param>
    template<class T1, typename T2>
    void construct(T1* p, const T2& value)
    {
        new(p) T1(value);
    }

    template <class T>
    void constructor(T* p, T&& val)
    {
        std::cout << "move constructor is called in construct.h" << std::endl;
        new (p) T(MessySTL::forward<T>(val));
    }

    template <class T, class... Args>
    void constructor(T* p, Args&&... args)
    {
        new (p) T(MessySTL::forward<Args>(args)...);
    }
    template<class T>
    void destroy(T* pointer)
    {
        pointer->~T(); //used destructor ~T()
    }

    // Forward declaration
    template<class ForwardIterator, class T>
    void _destroy(ForwardIterator first, ForwardIterator last, T*);
    template<class ForwardIterator>
    void _destroy_aux(ForwardIterator first, ForwardIterator last, _true_type);
    template<class ForwardIterator>
    void _destroy_aux(ForwardIterator first, ForwardIterator last, _false_type);

    /// <summary>
    /// This version of destroy function deconstruct a lists of
    /// objects within the range of two iterators.
    /// </summary>
    /// <typeparam name="ForwardIterator"></typeparam>
    /// <param name="first"></param>
    /// <param name="last"></param>
    template<class ForwardIterator>
    void destroy(ForwardIterator first, ForwardIterator last)
    {
        _destroy(first, last, value_type(first)); // value_type() return temporary object -> a pointer 
    }

    template<class ForwardIterator, class T>
    void _destroy(ForwardIterator first, ForwardIterator last, T*)
    {
        typedef typename _type_traits<T>::has_trivial_destructor trivial_destructor; 
        _destroy_aux(first, last, trivial_destructor()); // trivial_destructor() is a temporary struct of true or false type
    }

    // if the object has trivial destrcutor, the program doesn't need to do anything
    template<class ForwardIterator>
    void _destroy_aux(ForwardIterator first, ForwardIterator last, _true_type)
    {
    }

    template<class ForwardIterator>
    void _destroy_aux(ForwardIterator first, ForwardIterator last, _false_type)
    {
        while (first < last)
        {
            destroy(&*first);
            first++;
        }
    }

}
#endif // !CONSTRUCT_H_
