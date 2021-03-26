#pragma once
#include "./pool_alloc.h"
#include "./iterator_base.h"

template <class T>
struct ListNode 
{
    ListNode* prev;
    ListNode* next;
    T data;
};
// list iterator
template<class T, class Pointer, class Reference>
struct ListIterator
{
    typedef ListIterator<T, Pointer, Reference>         this_type;
    typedef ListIterator<T, T*, T&>                     iterator;
    typedef ListIterator<T, const T*, const T&>         const_iterator;
    typedef size_t                                      size_type;
    typedef ptrdiff_t                                   difference_type;
    typedef T                                           value_type;
    typedef ListNode<T>                                 node_type;
    typedef Pointer                                     pointer;
    typedef Reference                                   reference;
    typedef MessySTL::bidirectional_iterator_tag        iterator_category;

public:
    node_type* mp_Node;
    
public:
    ListIterator() noexcept;
    ListIterator(node_type* p_Node) noexcept;
    ListIterator(const iterator& x) noexcept;
    this_type next() const noexcept;
    this_type prev() const noexcept;

    reference operator*() const noexcept;
    pointer operator->() const noexcept;
};
template<class T, class alloc = MessySTL::pool_alloc<T>>
class List
{
public:
    // constructor
    // destructor
    // operator

    // ------------------ iterator -------------
    //begin
    //end
    //cbegin
    //cend

    // ------------------ Capacity -------------
    // empty
    // size
    // max_size
    
    // ------------------ Element access -------------
    // front
    // back

    // ------------------ Modifiers -------------
    // assign
    // emplace_front
    // push_front
    // pop_front
    // emplace_back
    // push_back
    // pop_back
    // emplace
    // insert
    // erase
    // swap
    // resize
    // clear

    // ------------------ Operations -------------
    // splice
    // remove
    // remove_if
    // unique
    // merge
    // sort
    // reverse
};

// List Iterator
template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::ListIterator() noexcept
{
}

template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::ListIterator(node_type* p_Node) noexcept
{
    mp_Node = p_Node;
}

template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::ListIterator(const iterator& x) noexcept
{
    mp_Node = x->mp_Node;
}

template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::this_type
ListIterator<T, Pointer, Reference>::next() const noexcept
{
    return ListIterator(mp_Node->prev());
}

template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::this_type
ListIterator<T, Pointer, Reference>::prev() const noexcept
{
    return ListIterator(mp_Node->prev());
}

template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::reference
ListIterator<T, Pointer, Reference>::operator*() const noexcept
{
    return mp_Node->data;
}

template<class T, class Pointer, class Reference>
inline ListIterator<T, Pointer, Reference>::pointer
ListIterator<T, Pointer, Reference>::operator->() const noexcept
{
    return &mp_Node->data;
}
