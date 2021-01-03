#pragma once

#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>


namespace MessySTL
{
    namespace test
    {
        template<class Container>
        void print_container(Container& container, const std::string& name = "") {//����ÿһ����������const_iterator
            std::cout << "Container " << name << " :";
            for (auto it : container)
            {
                std::cout << " " << it << " ";
            }
            std::cout << std::endl;
        }

        template<class Container1, class Container2>
        bool container_equal(Container1& con1, Container2& con2) {//����ÿһ����������const_iterator
            auto first1 = std::begin(con1), last1 = std::end(con1);
            auto first2 = std::begin(con2), last2 = std::end(con2);
            for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
                if (*first1 != *first2)
                    return false;
            }
            return (first1 == last1 && first2 == last2);
        }

        // ���ͨ����ʾ
        #define PASSED    std::cout << "[ PASSED ]\n"

        // �����������
        #define COUT(container) do {                             \
          std::string con_name = #container;                     \
          std::cout << " " << con_name << " :";                  \
          for (auto it : container)                              \
            std::cout << " " << it;                              \
          std::cout << "\n";                                     \
        } while(0)

        // ����������ú�����Ľ��
        #define FUN_AFTER(con, fun) do {                         \
          std::string fun_name = #fun;                           \
          std::cout << " After " << fun_name << " :\n";          \
          fun;                                                   \
          COUT(con);                                             \
        } while(0)
    }
}
