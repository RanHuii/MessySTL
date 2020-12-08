#include <iostream>
#include "../header/vector.h"
#include "../header/iterator_base.h"
#include "../header/construct.h"
#include "../header/pool_alloc.h"

struct A
{
    A() {
        counter++;
        std::cout << " A Constructed!" << std::endl;
    }
    ~A()
    {
        std::cout << " A Destructed!" << std::endl;
    }

    static int counter;
};
size_t round_up(size_t byte)
{
    return (byte + 7) & ~7;
}
int A::counter = 0;

// function with lvalue and rvalue reference overloads:
void overloaded(const int& x) { std::cout << "[lvalue]"; }
void overloaded(int&& x) { std::cout << "[rvalue]"; }

// function template taking rvalue reference to deduced type:
template <class T> void fn(T&& x) {
    overloaded(x);                   // always an lvalue
    overloaded(std::forward<T>(x));  // rvalue if argument is rvalue
}


int main()
{
    typedef MessySTL::pool_alloc<int> alloc;
    MessySTL::vector<int, MessySTL::pool_alloc<int>> vec;
    MessySTL::vector<int, MessySTL::pool_alloc<int>> vec1(3);

    MessySTL::vector<int, MessySTL::pool_alloc<int>>::iterator it = vec1.begin();
    std::cout << vec1.size() << std::endl;
    std::cout << *it << std::endl;
}