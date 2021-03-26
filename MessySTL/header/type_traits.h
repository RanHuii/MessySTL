#pragma once

#ifndef _TYPE_TRAITS_H
#define _TYPE_TRAITS_H

// use standard header for type_traits
#include <type_traits>

namespace MessySTL
{
    // tag types
    struct _true_type {};
    struct _false_type {};

    /*
    * This type traits help compiler construct and destory class 
    * If a class has trivial constructor, assignment operator, 
    * destructor, it will be more efficient to use function to 
    * directly manipulate the memory e.g. malloc() and memcpy(),
    * instead of using the constructor.
    * 
    * If the class doesn't have trivial constructor etc, we have
    * to call the constructor.
    * 
    */


    /// <summary>
    /// Use _false_type as the default type
    /// so that no class will be failed due to misjuedgement on
    /// trivial and non-trivial object
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<class T>
    struct _type_traits {
        typedef _false_type     has_trivial_default_constructor;
        typedef _false_type     has_trivial_copy_constructor;
        typedef _false_type     has_trivial_assignment_operator;
        typedef _false_type     has_trivial_destructor;
        typedef _false_type     is_POD_type; // Plain old Data, a class without 
                                             // explicit constructors, destructors, copy/move constructor and operator
                                             // and virtual members

    };
    // Provide some specializations
    //template partial specification
    template<>
    struct _type_traits<bool> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<char> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<unsigned char> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<wchar_t> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<short> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<unsigned short> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<int> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<unsigned int> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<long> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<unsigned long> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<long long> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<unsigned long long> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<float> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<double> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<long double> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<class T>
    struct _type_traits<T*> {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<class T>
    struct _type_traits<const T*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<char*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<unsigned char*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<signed char*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<const char*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<const unsigned char*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    template<>
    struct _type_traits<const signed char*>
    {
        typedef _true_type      has_trivial_default_constructor;
        typedef _true_type      has_trivial_copy_constructor;
        typedef _true_type      has_trivial_assignment_operator;
        typedef _true_type      has_trivial_destructor;
        typedef _true_type      is_POD_type;
    };

    // numeric limits
    template<class T>
    struct _Is_integer {
        typedef _false_type _Integral;
    };

    template<>
    struct _Is_integer<bool> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<char> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<signed char> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<unsigned char> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<wchar_t> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<short> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<unsigned short> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<int> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<unsigned int> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<long> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<unsigned long> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<long long> {
        typedef _true_type _Integral;
    };

    template<>
    struct _Is_integer<unsigned long long> {
        typedef _true_type _Integral;
    };
}


   

#endif // !_TYPE_TRAITS_H
