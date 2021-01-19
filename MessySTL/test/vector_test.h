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
                int_vector v1;
                int_vector v2(10);
                int_vector v3(10, 1);
                int_vector v5(v2);
                int_vector v6(MessySTL::move(v2));
                const int_vector v8(3, 1);
                FUN_AFTER(v1, v1.push_back(2));
                FUN_AFTER(v1, v1.assign(3, 2));
                FUN_AFTER(v1, v1.push_back(6));
                FUN_AFTER(v1, v1.push_back(7));
                FUN_AFTER(v1, v1.insert(v1.end(), 6));
                FUN_AFTER(v1, v1.insert(v1.begin(), 2, 3));
                FUN_AFTER(v1, v1.erase(v1.begin()));
                FUN_AFTER(v1, v1.erase(v1.begin(), v1.begin() + 2));
                FUN_AFTER(v1, v1.resize(2));
                FUN_AFTER(v1, v1.resize(3, 3));
                FUN_AFTER(v2, v2.assign(v1.begin(), v1.end()));
                FUN_AFTER(v2, v2.assign(v2.begin(), v2.end()));
                FUN_AFTER(v2, v2.clear());
                FUN_AFTER(v2, v2.push_back(6));
                FUN_AFTER(v2, v2.pop_back());
                FUN_AFTER(v2, v2.emplace(v2.begin(), 0));
                FUN_AFTER(v2, v2.emplace_back((2)));
                
                v6 = MessySTL::move(v2);
                FUN_VALUE(v6.size());
                FUN_VALUE(v2.size());
                FUN_VALUE(*v6.begin());
                FUN_VALUE(v6.front());
                v6.front() += v6.back();
                v6.back() += v6.front();
                FUN_VALUE(v6.front());
                FUN_VALUE(v6.back());
                FUN_VALUE(v6.at(0));
                
                std::cout << "Before changing v3.data(): " << std::endl;
                COUT(v3);
                int* p = v3.data();
                *p = 10;
                *++p = 20;
                p[1] = 30;
                std::cout << "After changing v3.data(): " << std::endl;
                COUT(v3);
                FUN_VALUE(v8.front());
                FUN_VALUE(v8.back());
                FUN_VALUE(v8.size());


            }
        }
    }
}
