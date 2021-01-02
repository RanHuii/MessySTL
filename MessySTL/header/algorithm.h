#pragma once

#include "iterator_base.h"
namespace MessySTL
{
    template<class Forward_iterator, class T>
    void fill(Forward_iterator first, Forward_iterator last, const T& value)
    {
        for (; first != last; ++first)
        {
            *first = value;
        }
    }

    template<class Forward_iterator, class Size, class T>
    Forward_iterator
        fill_n(Forward_iterator first, Size count, const T& value)
    {
        for (Size i = 0; i < count; i++)
        {
            *first++ = value;
        }
        return first;
    }

    // return the iterator one passed the last element
    template<class Input_iterator, class Forward_iterator>
    Forward_iterator
        copy(Input_iterator first, Input_iterator last, Forward_iterator result)
    {
        for (;first != last; ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template<class Input_iterator, class Size, class Forward_iterator>
    Forward_iterator
        copy_n(Input_iterator first, Size n, Forward_iterator result)
    {
        for (Size i = 0; i < n; i++, first++, result++)
        {
            *result = *first;
        }
        return result;
    }

    template<class Input_iterator, class Forward_iterator>
    Forward_iterator
        copy_trivial(Input_iterator first, Input_iterator last, Forward_iterator result)
    {   
        const auto n = static_cast<size_t>(last - first);
        if (n > 0)
        {
            memmove(result, first, sizeof(value_type(first)) * (last - first));
        }
        
        return result + (last - first);
    }

    /*
    * Copies the elements in the range [first, last) starting from the end into the range terminating at result
    */
   template<class BidirectionalItertor1, class BidirectionalIterator2>
   BidirectionalIterator2 copy_backward(BidirectionalItertor1 first,
       BidirectionalItertor1 last,
       BidirectionalIterator2 result)
   {
       while (last != first)
       {
           *(--result) = *(--last);
           return result;
       }
   }
}