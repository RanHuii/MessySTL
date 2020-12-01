#include <iostream>
#include "../header/construct.h"


struct A
{
    A() {
        std::cout << " A Constructed!" << std::endl;
    }
    ~A()
    {
        std::cout << "A Destructed!" << std::endl;
    }
};
int main()
{
    A();
    A();
    A();
    A a = A();
}