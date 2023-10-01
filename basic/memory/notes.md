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
3. 指定内存回收逻辑
4. std::make_shared
5. 支持数组 (C++17 shared_ptr<T[]>; c++20 支持 make_shared 分配内存)
