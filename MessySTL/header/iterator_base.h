#pragma once

#ifndef _ITERATOR_BASE_H_
#define _ITERATOR_BASE_H_

namespace MessySTL {
    
    // tag_types
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {} ;
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    // T: the value type
    // _Distance: the unit difference of T.
    template<class T, class Distance>
    struct input_iterator {
        typedef input_iterator_tag  iterator_category;
        typedef T                   value_type;
        typedef Distance            difference_type;
        typedef T*                  pointer;
        typedef T&                  reference;
    };

    struct output_iterator {
        typedef output_iterator_tag iterator_category;
        typedef void                value_type;
        typedef void                difference_type;
        typedef void                pointer;
        typedef void                reference;
    };

    template<class T, class Distance>
    struct forward_iterator {
        typedef forward_iterator_tag  iterator_category;
        typedef T                     value_type;
        typedef Distance              difference_type;
        typedef T*                    pointer;
        typedef T&                    reference;
    };

    template<class T, class Distance>
    struct bidrectional_iterator {
        typedef bidirectional_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef Distance                    difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    template<class T, class Distance>
    struct random_access_iterator {
        typedef random_access_iterator  iterator_category;
        typedef T                       value_type;
        typedef Distance                difference_type;
        typedef T*                      pointer;
        typedef T&                      reference;
    };
   
    template<class Category,
             class T,
             class Distance,
             class Pointer, 
             class Reference>
        struct iterator{

    };

}

#endif
