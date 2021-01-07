#pragma once

// This file contains utility functions, including move, forward, swap etc..

#include <cstddef>

#include "type_traits.h"

namespace MessySTL
{
    
    /*
    * Here T&& is a universal reference
    * it depends on the expression that is passed in.
    * If the expression is lvalue, arg will be lvalue reference.
    * If the expression is rvalue, arg will be rvalue reference as we want.
    * We need an extra step to guarantee that we can return rvalue no matter what.
    * We remove the referenceness first by std::remove_reference, then add it back on(&&)
    */
    template<class T>
    typename std::remove_reference<T>::type&& 
    move(T&& param) noexcept
    {
        using ReturnType = typename std::remove_reference<T>::type&&;
        return static_cast<ReturnType>(param);
    }

    template<class T>
    T&& 
        forward(typename std::remove_reference<T>::type& param) noexcept // forward an lvalue as either an lvalue or an rvalue
    {
        return static_cast<T&&>(param); 
    }

    template<class T>
    T&&
        forward(typename std::remove_reference<T>::type&& param) noexcept // forward an rvalue as an rvalue
    {
        static_assert(!std::is_lvalue_reference<T>::value, "bad forward call"); 
        return static_cast<T&&>(param);
    }

    template<class T>
    void swap(T& lhs, T& rhs)
    {
        auto tmp(MessySTL::move(lhs));
        lhs = MessySTL::move(rhs);
        rhs = MessySTL::move(tmp);
    }



}