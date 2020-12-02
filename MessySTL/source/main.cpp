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


int main()
{
    MessySTL::_false_type false_type;
   
    std::vector<A> vec;
    vec.reserve(3);
    vec.emplace_back(A());
    vec.emplace_back(A());
    vec.emplace_back(A());
    std::vector<A>::iterator start = vec.begin();
    std::vector<A>::iterator end = vec.end();
    ptrdiff_t n = end - start;
    std::cout << "pointer different is: " << n << std::endl;
    MessySTL::_destroy_aux(start, end, false_type);
    int* p = new int(10);
    MessySTL::destroy(p);

}