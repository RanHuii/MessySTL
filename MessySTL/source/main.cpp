#include <iostream>

#include "../test/vector_test.h"
#include <vector>

template<class ...Us> void f(Us... pargs) 
{
    double result = 0;
    result =  (pargs+...) ;
    std::cout << result << std::endl;
}
template<class ...Ts> void g(Ts... args) {
    f(args...); // ��&args...�� �ǰ�չ��
                 // ��&args�� ����ģʽ
}

int main()
{
    using namespace MessySTL::test;
    g(1, 2, 3, 4, 5);
    vector_test::vector_test();

   
}