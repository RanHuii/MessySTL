#pragma once

// vector test

#include "../header/vector.h"
#include <iostream>
#include "../test/test.h"
#include "../header/alloc.h"
#include "../header/allocator.h"

namespace MessySTL
{
    namespace test
    {
        namespace vector_test
        {
            

            void vector_test()
            {
                
                int a[] = { 1, 2, 3, 4, 5 };
                using int_vector = MessySTL::vector<int, pool_alloc<int>>;

                int_vector v2(10);
                int_vector v3(10, 1);
                int_vector v5(v2);
                int_vector v6(std::move(v2));
            

                int_vector v1;
                FUN_AFTER(v1, v1.push_back(2));
                FUN_AFTER(v1, v1.assign(3, 2));
                
                FUN_AFTER(v1, v1.push_back(6));
                FUN_AFTER(v1, v1.push_back(7));
                FUN_AFTER(v1, v1.insert(v1.end(), 6));
                FUN_AFTER(v1, v1.insert(v1.begin(), 2, 3));
                /*FUN_AFTER(v1, v1.push_back(6));
                FUN_AFTER(v1, v1.push_back(6));
                FUN_AFTER(v1, v1.end());
                FUN_AFTER(v1, v1.begin());*/

                
                // FUN_AFTER(v1, v1.insert(v1.end(), 7));

                // FUN_AFTER(v1, v1.insert(v1.begin() + 1, 2, 3));

            }
        }
    }
}
