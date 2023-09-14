#include <iostream>
#include <new>

struct alignas(256) Str{};

int main()
{
    Str* x = new Str();
    std::cout << x << std::endl;
} 