# 动态内存管理
## new & delete
1. 构造单一对象 / 对象数组

```cxx
new int; new int[5]; new int[5]{1}; delete[] x;
```

2. nothrow new

```cxx
// 不加nothrow：分配失败会直接进入异常处理，不会进行以下的判断。
int* x = new (std::nothrow) int[5]{};
if (x == nullptr) {}
```

3. placement new
   1. 在已经分配好的内存上构造对象。

```cxx
// 首先得是合法指针，其次所指向空间够。
char ch[sizeof(int)];
int* x = new (ch) int(2);
{}
```
```cxx
/*
行为不可预期。
fun函数结束后，栈内存ch会被销毁。
*/
int* fun()
{
    char ch[sizeof(int)];
    int* x = new (ch) int(2);
    return x;
}

int main()
{
    int* x = fun();
    std::cout << *x << std::endl;
}
```

4. new auto
   1. `int* x = new auto(2);`

5. new与对象对齐

```cxx
struct alignas(256) Str{};

int main()
{
    // 开辟的内存的首地址是256的整数倍。
    Str* x = new Str();
    std::cout << x << std::endl;
} 
```

6. placement delete
    1. 只销毁不回收，销毁的空间之后可以给placement new用。


## 智能指针
### shared_ptr
1. 基本用法
2. reset / get 方法
    ```cxx
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
    
    int main()
    {
        std::shared_ptr<Foo> sptr = std::make_shared<Foo>(1);
        std::cout << "The first Foo's bar is " << sptr->getBar() << "\n";
    
        // 重置，交与新的 Foo 实例
        // （此调用后将销毁旧实例）
        sptr.reset(new Foo);
        std::cout << "The second Foo's bar is " << sptr->getBar() << "\n";
        /*
        Foo: constructor, bar = 1
        The first Foo's bar is 1
        Foo: constructor, bar = 0
        Foo: destructor, bar = 1
        The second Foo's bar is 0
        Foo: destructor, bar = 0
        */
    }
    ```
    get(): 返回存储的指针
    ```cxx
    #include <iostream>
    #include <memory>
    #include <string_view> // c++17
    
    void output(std::string_view msg, int const* pInt)
    {
        std::cout << msg << *pInt << "\n";
    }
    
    int main()
    {
        int* pInt = new int(42);
        std::shared_ptr<int> pShared = std::make_shared<int>(42);
    
        output("Naked pointer ", pInt);
        // output("Shared pointer ", pShared); // 编译错误
        output("Shared pointer with get() ", pShared.get());
    
        delete pInt;

        /*
        Naked pointer 42
        Shared pointer with get() 42
        */
    }
    ```
3. 指定内存回收逻辑
    ```cxx
    void diy_del(int* ptr)
    {
        std::cout << "Call deleter fun\n";
        delete ptr;
    }

    int main()
    {
        // Call deleter fun
        std::shared_ptr<int> x(new int(2), diy_del);
    }

    /*
    针对静态变量的指针的析构，不应该使用delete来销毁内存，因为静态变量的内存应该是整个程序结束之后自动释放的。所以此时可以使用重定义deletor来避免默认的delete释放内存。
    */
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
    ```
4. std::make_shared
    
    shared_ptr的构造函数会申请两次内存，而make_ptr会申请一次内存。一方面效率提交了，一方面保证了异常安全

5. 支持数组 (C++17 shared_ptr<T[]>; c++20 支持 make_shared 分配内存)

### unique_ptr
1. 基本用法
2. unique_ptr 不支持复制，但可以移动
3. 为 unique_ptr 指定内存回收逻辑

### weak_ptr
1. 基于 shared_ptr 构造
2. lock 方法


## 动态内存相关问题
1. sizeof 不会返回动态分配的内存大小
2. 使用分配器（allocator）来分配内存
3. 使用 malloc/free 来管理内存
4. 使用 aligned_alloc 来分配对齐内存
5. 动态内存与异常安全
6. C++对于垃圾回收的支持
