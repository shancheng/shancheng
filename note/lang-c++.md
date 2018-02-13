http://en.wikipedia.org/wiki/Rule_of_three_(C++\_programming)

https://stackoverflow.com/questions/1434937/namespace-functions-versus-static-methods-on-a-class


# C++ books

Modern C++ Design

An Introduction to Boost

Thinking in C++

Effective C++

More Effective C++

Exceptional C++

More Exceptional C++

Exceptional C++ Style

C++ Coding Standard

Writing Clean Code

[Guru of the Week](http://www.gotw.ca/gotw/)


# C++ template

http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

## STL

###### STL引入函数对象的原因

函数指针不能满足STL对抽象性的要求。

函数指针不能满足软件积木的要求，无法和STL其它组件搭配，产生灵活的变化。

###### Iterator

Input Iterator：只能单步向前迭代元素，不允许修改由该类迭代器引用的元素。

Output Iterator：该类迭代器和Input Iterator极其相似，也只能单步向前迭代元素，不同的是该类迭代器对元素只有写的权力。

Forward Iterator：该类迭代器可以在一个正确的区间中进行读写操作，它拥有Input Iterator的所有特性，和Output Iterator的部分特性，以及单步向前迭代元素的能力。

Bidirectional Iterator：该类迭代器是在Forward Iterator的基础上提供了单步向后迭代元素的能力。

Random Access Iterator：该类迭代器能完成上面所有迭代器的工作，它自己独有的特性就是可以像指针那样进行算术计算，而不是仅仅只有单步向前或向后迭代。


# C++ macro and inline

###### 宏的缺点
宏看起来像一个函数调用，但不总是这样。

预处理器不允许访问类的成员数据。

###### 宏的应用场合

字符串定义。

字符串拼接。用#指示，它允许取一个标识符并把它转化为字符数组。

标志性粘贴。用##指示，它允许设两个标识符并把它们粘贴在一起自动产生一个新的标识符

Examples

```c++
__FILE__
__FUNCTION__
__LINE__

#define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#define zDebug(msg, ...) fprintf(stderr, msg, ## __VA_ARGS__);
#define NEW(class_, ...) new class_(__VA_ARGS__)
#define CONNECT(a, b) a##b
```


# C++ build systems

http://www.gnu.org/prep/standards/html_node/Makefile-Conventions.html

http://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html

http://www.ibm.com/developerworks/cn/linux/l-makefile/index.html

qmake (generate Makefile from .pro file)

MPC (The Makefile, Project and Workspace Creator)

Jam and Boost.Jam

http://stackoverflow.com/questions/1368746/optimization-in-gcc

http://www.gentoo.org/doc/zh_cn/gcc-optimization.xml
