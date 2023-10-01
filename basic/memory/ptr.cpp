#include <iostream>
#include <memory>

void func1()
{
    std::shared_ptr<int> x(new int(2));
}

int main()
{
    func1();

    return 0;
}