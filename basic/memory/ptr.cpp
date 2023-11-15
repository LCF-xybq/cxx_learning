#include <memory>
#include <iostream>
#include <string_view>


struct Foo {
    Foo(int n = 0) noexcept : bar(n) {
        std::cout << "Foo: constructor, bar = " << bar << '\n';
    }
    ~Foo() {
         std::cout << "Foo: destructor, bar = " << bar << '\n';
    }
    int getBar() const noexcept { return bar; }
private:
    int bar;
};

void output(std::string_view msg, int const* pInt)
{
    std::cout << msg << *pInt << "\n";
}

void fun1()
{
    std::shared_ptr<Foo> sptr = std::make_shared<Foo>(1);
    std::cout << "The first Foo's bar is " << sptr->getBar() << "\n";
 
    // 重置，交与新的 Foo 实例
    // （此调用后将销毁旧实例）
    sptr.reset(new Foo);
    std::cout << "The second Foo's bar is " << sptr->getBar() << "\n";
}

void fun2()
{
    int* pInt = new int(42);
    std::shared_ptr<int> pShared = std::make_shared<int>(42);
 
    output("Naked pointer ", pInt);
    // output("Shared pointer ", pShared); // 编译错误
    output("Shared pointer with get() ", pShared.get());
 
    delete pInt;
}

void diy_del(int* ptr)
{
    std::cout << "Call deleter fun\n";
    delete ptr;
}

void dummy(int* ptr) {}

std::shared_ptr<int> fun3()
{
    static int res = 2;
    return std::shared_ptr<int>(&res, dummy);
}

int main()
{
    {
        std::shared_ptr<int> x = fun3();
    }
}