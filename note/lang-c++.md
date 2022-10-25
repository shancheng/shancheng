http://en.wikipedia.org/wiki/Rule_of_three_(C++\_programming)

https://stackoverflow.com/questions/1434937/namespace-functions-versus-static-methods-on-a-class




# C++ books and resources

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




# C++ error handling

https://www.codeproject.com/Articles/38449/C-Exceptions-Pros-and-Cons

https://stackoverflow.com/questions/1849490/c-arguments-for-exceptions-over-return-codes

## abort, terminate and exit

http://stackoverflow.com/questions/2820285/abort-terminate-or-exit

abort不做任何处理

```
#0 0x0000003880a2ffc5 in raise () from /lib64/libc.so.6
#1 0x0000003880a31a70 in abort () from /lib64/libc.so.6
#2 0x0000000000400819 in f () at test.cpp:34
#3 0x000000000040082d in g () at test.cpp:40
#4 0x0000000000400876 in h () at test.cpp:45
#5 0x00000000004008a4 in main (argc=1, argv=0x7fffffffe388) at test.cpp:53
```

exit会处理全局对象和静态对象，但不进行stack unwinding

```
#0 GlobalObject::~GlobalObject (this=0x600c68, __in_chrg=<value optimized out>) at test.cpp:24
#1 0x00000000004005ce in __tcf_0 () at test.cpp:47
#2 0x0000003880a33255 in exit () from /lib64/libc.so.6
#3 0x0000000000400636 in f () at test.cpp:32
#4 0x000000000040064f in g () at test.cpp:39
#5 0x0000000000400667 in h () at test.cpp:44
#6 0x0000000000400686 in main (argc=1, argv=0x7fffffffe388) at test.cpp:51
```

如果异常没有捕捉，会调用std::terminate

```
#0 0x0000003880a2ffc5 in raise () from /lib64/libc.so.6
#1 0x0000003880a31a70 in abort () from /lib64/libc.so.6
#2 0x00000038934bed94 in __gnu_cxx::__verbose_terminate_handler() () from /usr/lib64/libstdc++.so.6
#3 0x00000038934bce46 in ?? () from /usr/lib64/libstdc++.so.6
#4 0x00000038934bce73 in std::terminate() () from /usr/lib64/libstdc++.so.6
#5 0x00000038934bcf71 in __cxa_throw () from /usr/lib64/libstdc++.so.6
#6 0x00000000004008d0 in f () at test.cpp:35
#7 0x00000000004008f7 in g () at test.cpp:39
#8 0x0000000000400940 in h () at test.cpp:44
#9 0x000000000040096d in main (argc=1, argv=0x7fffffffe388) at test.cpp:50
```

通过set_terminate可以设定一下异常处理函数，但是程序结束后依然会abort

```
#0 myterminate () at test.cpp:53
#1 0x00000038934bce46 in ?? () from /usr/lib64/libstdc++.so.6
#2 0x00000038934bce73 in std::terminate() () from /usr/lib64/libstdc++.so.6
#3 0x00000038934bcf71 in __cxa_throw () from /usr/lib64/libstdc++.so.6
#4 0x0000000000400bc8 in f () at test.cpp:40
#5 0x0000000000400bef in g () at test.cpp:44
#6 0x0000000000400c38 in h () at test.cpp:49
#7 0x0000000000400c6f in main (argc=1, argv=0x7fffffffe388) at test.cpp:60

#0 0x0000003880a2ffc5 in raise () from /lib64/libc.so.6
#1 0x0000003880a31a70 in abort () from /lib64/libc.so.6
#2 0x00000038934bce4b in ?? () from /usr/lib64/libstdc++.so.6
#3 0x00000038934bce73 in std::terminate() () from /usr/lib64/libstdc++.so.6
#4 0x00000038934bcf71 in __cxa_throw () from /usr/lib64/libstdc++.so.6
#5 0x0000000000400bc8 in f () at test.cpp:40
#6 0x0000000000400bef in g () at test.cpp:44
#7 0x0000000000400c38 in h () at test.cpp:49
#8 0x0000000000400c6f in main (argc=1, argv=0x7fffffffe388) at test.cpp:60
```

## assert

assert宏的原型定义在<assert.h>中，其作用是如果它的条件返回错误，则终止程序执行

assert()频繁的调用会极大的影响程序的性能，增加额外的开销。在调试结束后，可以通过在包含#include <assert.h>的语句之前插入 #define NDEBUG 来禁用assert调用

## C++ exception

[Overview of x64 Calling Conventions](https://msdn.microsoft.com/en-us/library/ms235286.aspx)

[How a C++ compiler implements exception handling](https://www.codeproject.com/articles/2126/how-a-c-compiler-implements-exception-handling)

[Java异常处理原则，check and Unchecked Exception](http://blog.51cto.com/wanqiufeng/465684)

[软件错误处理原则 局部问题缩小，全局问题放大](http://club.topsage.com/thread-657437-1-1.html)

## My coding standards

All exceptions should derive from a base class Exception
- Class Exception is a subclass of std::runtime_error
- Class Exception has a error level to indicate it's critical or not

Outermost functions (main and Thread::Run)
- Catch std::exception
- Set suitable error code when catches an exception
- [Catch (abi::__forced_unwind&) and rethrow to forbid aborting caused by pthread_exit and pthread_cancel](https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown)
- Catch (...)

Normal functions
- Distinguish normal exceptions and critical exceptions
- Handle normal exceptions
- Forward critical exceptions
- A class is normal if the exception is derived from Exception and its error level is normal, all other exceptions are critical




# C++11

[理解 C++ 的 Memory Order](http://senlinzhan.github.io/2017/12/04/cpp-memory-order/)

[关于Singleton中使用DCLP和Memory barrier的一点疑问？](https://www.zhihu.com/question/35522476)

[C++11 修复了双重检查锁定问题](http://blog.jobbole.com/52164/)

[Double-Checked Locking is Fixed In C++11](https://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/)

[Why Memory Barrier？](http://www.cnblogs.com/foohack/p/3582217.html)




# C++ build systems

http://www.gnu.org/prep/standards/html_node/Makefile-Conventions.html

http://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html

http://www.ibm.com/developerworks/cn/linux/l-makefile/index.html

qmake (generate Makefile from .pro file)

MPC (The Makefile, Project and Workspace Creator)

Jam and Boost.Jam

http://stackoverflow.com/questions/1368746/optimization-in-gcc

http://www.gentoo.org/doc/zh_cn/gcc-optimization.xml




# Portability

###### How to print abstract data items?

https://lwn.net/Kernel/LDD3/

The main problem with _t data items is that when you need to print them, it’s not always easy to choose the right printk or printf format, and warnings you resolve on one architecture reappear on another. For example, how would you print a size_t, that is unsigned long on some platforms and unsigned int on some others?