#include <iostream>
#include <vector>
#include "../header/iterator_base.h"
#include "../header/construct.h"


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
    MessySTL::_false_type false_type;

    char* p = new char('a');
    std::cout << p << std::endl;
    int* q = (int*)p;
    char* w = (char*)q;
    std::cout << q << std::endl;
    std::cout << w << std::endl;
    delete p;
   /* delete w;
    delete q;*/
    

}