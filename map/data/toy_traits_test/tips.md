## tips

当我们在`iterator`中定义了

```c++
template<class T>
class container{
  	...  
    class iterator{
    	...
        using value_type = T;
        ...
    }
    ...
}
```

定义模板结构体`iterator_traits`:

```c++
template<typename T>
struct iterator_traits{
    using value_type = typename T::value_type
};
```

使用时

```c++
container<U> c;
iterator_traits<container::iterator>::value_type //U
```

* **注意typename的使用**

## 参考链接

https://zhuanlan.zhihu.com/p/315014147

https://en.cppreference.com/w/cpp/iterator/iterator_traits