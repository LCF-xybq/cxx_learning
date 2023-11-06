# 序列与关联容器
## 序列容器
1. array：元素个数固定
    1. 与内建数组相比提供了复制操作
    2. 元素访问：[], at, front, back, data
    3. 容量相关：empty, size, max_size
    4. 填充与交换：fill, swap
    
2. vector: 元素连续存储
    1. 容量相关：capacity / reverse / shrink_to_fit
    2. 附加元素：push_back / emplace_back
    3. 插入元素：insert / emplace
    4. 元素删除：pop_back / erase / clear
    5. 写操作可能会导致迭代器失效
3. forward_list/list：基于链表/双向链表
4. deque：vector与list的折衷
    1. push_back / push_front 速度较快
    2. 在序列中间插入、删除速度较慢
5. basic_string：提供对字符串专门支持

## 关联容器
1. 使用键进行索引
2. set / map / multiset / multimap 底层使用红黑树实现
3. unordered_set / unordered_map / unordered_multiset / unordered_multimap 底层使用 hash 表实现
4. set，set迭代器所指向的对象是 const的，不能通过其修改元素
    1. 插入元素：insert / emplace / emplace_hint
    2. 删除元素：erase
    3. 访问元素：find / contains
    4. 修改元素：extract
5. map，树中的每个结点是一个 std::pair
    1. 迭代器所指向的对象是 std::pair，其键是 const类型
    2. [] 操作不能用于常量对象    
6. multiset / multimap
    1. 允许重复键
    2. find 返回首个查找到的元素
    3. count 返回元素个数
    4. lower_bound / upper_bound / equal_range 返回查找到的区间
7. unordered_set / unordered_map / unordered_multiset / unordered_multimap
    1. 与 set / map 相比查找性能更好，但插入操作一些情况下会慢
    2. 键需要支持 '转换为 hash值' 和 '判等' 两个操作
    3. 除 == != （速度较慢）外，不支持容器级的关系运算
8. 自定义 hash 与判等函数    
