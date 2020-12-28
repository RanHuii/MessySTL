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
#if 0

#endif
    typedef MessySTL::pool_alloc<int> alloc;

    MessySTL::vector<int, MessySTL::pool_alloc<int>> vec;
    MessySTL::vector<int, MessySTL::pool_alloc<int>> vec1(3,2);

    MessySTL::vector<int, MessySTL::pool_alloc<int>>::iterator it = vec1.begin();
   
    MessySTL::vector<int, MessySTL::pool_alloc<int>> copy_vec = vec1;
    MessySTL::vector<int, MessySTL::pool_alloc<int>> move_vec(MessySTL::vector<int, MessySTL::pool_alloc<int>>(3, 5));
    move_vec.push_back(4);
    copy_vec.print();
    move_vec.print();
    std::cout << copy_vec.size() << std::endl;
}