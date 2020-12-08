#pragma once

#include "iterator_base.h"
#include "type_traits.h"
#include "construct.h"
#include "algorithm.h"
/// <summary>
/// This file contains 5 functions to construct objects for 
/// uninitialized space
/// </summary>
namespace MessySTL
{

    template<class Input_iterator, class Forward_iterator>
    Forward_iterator
        uninitialized_copy(Input_iterator first, Input_iterator last, Forward_iterator result)
    {
        return uninitialized_copy(first, last, result, value_type(first));
    }

    template<class Input_iterator, class Forward_iterator, class T>
    Forward_iterator
        uninitialized_copy(Input_iterator first, Input_iterator last, Forward_iterator result, T*) // why value type doesn't return the actually type but a pointer to the type
    {
        typedef _type_traits<T>::is_POD_type is_POD_type;
        return unintialized_copy_aux(first, last, result, is_POD_type());
    }

    template<class Input_iterator, class Forward_iterator>
    Forward_iterator
        uninitialized_copy_aux(Input_iterator first, Input_iterator last, Forward_iterator result, _true_type)
    {
        MessySTL::copy(first, last, result);
    }

    template<class Input_iterator, class Forward_iterator>
    Forward_iterator
        uninitialized_copy_aux(Input_iterator first, Input_iterator last, Forward_iterator result, _false_type)
    {
        Forward_iterator cur = result;
        for (;first != last; ++first, ++cur)
        {   
            // should be fine to use ptrdiff_t
            construct(&*cur, *first);   // do it one by one.
        }
        return cur;
    }

    // uninitialized_fill
    template<class Forward_iterator, class T>
    void
    uninitialized_fill(Forward_iterator first, Forward_iterator last, const T& value)
    {
        uninitialized_fill(first, last, value, value_type(first));
    }

    template<class Forward_iterator, class T>
    void
        uninitialized_fill(Forward_iterator first, Forward_iterator last, const T& value, T*)
    {
        typedef _type_traits<T>::is_POD_type is_POD_type;
        return uninitialized_fill(first, last, value, is_POD_type());
    }

    template<class Forward_iterator, class T>
    void
        uninitialized_fill_aux(Forward_iterator first, Forward_iterator last, const T& value, _true_type)
    {
        typedef iterator_traits<first>::difference_type difference_type;
        difference_type n = last - first;
        if (n > 0)
        {
            return std::fill(first, last, value);
        }
    }

    template<class Forward_iterator, class T>
    void
        uninitialized_fill_aux(Forward_iterator first, Forward_iterator last, const T& value, _false_type)
    {
        typedef iterator_traits<first>::difference_type difference_type;
        difference_type n = last - first;
        if (n > 0)
        {
            for (;first != last; ++first)
            {
                constructor(&*first, value);
            }
        }
        
        return;
    }

    // ********************************************
    // uninitialized_fill_n


    // forward declaration
    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        uninitialized_fill_n_aux(Forward_iterator first, Size n, const T& value, T*);

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        uninitialized_fill_n_aux(Forward_iterator first, Size n, const T& value, _true_type);

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        uninitialized_fill_n_aux(Forward_iterator first, Size n, const T& value, _false_type);

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
    uninitialized_fill_n(Forward_iterator first, Size n, const T& value)
    {
        return uninitialized_fill_n_aux(first, n, value, value_type(first));
    }

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        uninitialized_fill_n_aux(Forward_iterator first, Size n, const T& value, T*)
    {
        typedef _type_traits<T>::is_POD_type is_POD_type;
        return uninitialized_fill_n_aux(first, n, value, is_POD_type());
    }

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        uninitialized_fill_n_aux(Forward_iterator first, Size n, const T& value, _true_type)
    {
        return MessySTL::fill_n(first, n, value);
    }

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        uninitialized_fill_n_aux(Forward_iterator first, Size n, const T& value, _false_type)
    {   
        Forward_iterator cur = first;
        for (Size i = 0; i < n; ++i, ++cur)
        {
            construct(&*cur, value);
        }
        return cur;
    }


}
