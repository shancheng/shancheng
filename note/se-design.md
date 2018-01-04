# Methodology

TDD

Scrum

Lean

OO

# UML

http://en.wikipedia.org/wiki/List_of_UML_tools
List of UML tools

UML是使用面向对象概念进行系统建模的一组表示法。
UML是一种建模语言；它对开发人员如何进行面向对象的分析和设计不提供指导，也不对开发过程的活动顺序提供指导。

http://www.umlchina.com/Chat/qiuyuhui200805.htm
邱郁惠--开源StarUML建模实战

Use Case
use case是对过程的文字化描述，用来描述一个参与者（一个外部的主动者）使用系统完成某个过程时的事件发生顺序，它展示和体现了其所描述的过程中的需求情况。
使用use case来标识并记录过程信息实际上并不是面向对象的分析和设计过程中的一项活动，因为它没有以对象观点为中心。
high-level use case以简洁的方式来描述一个过程。
expanded use case在high-level use case的基础上更加详细地描述过程。它与high-level use case的主要区别就是含有“典型的事件发生过程”。
real use case能够具体描述过程中的真实细节，以及具体的输入输出等技术。理想的情况是在一个开发周期的设计阶段创建real use case，因为real use case是设计阶段的制品。
应该提高优先级的use case包括：

- 对体系结构设计有重要影响的use case；

- 不需要花费很多努力就可以从中获得重要信息和线索的use case；

- 含有开发风险、时间紧迫或功能复杂的use case；

- 涉及到重要技术研究或者新技术和高风险的use case；

- 代表主要的在线业务流程的use case；

- 能产生直接经济效益或者降低成本的use case。

参与者

- 参与者是系统外部的一个实体。参与者通常是通过向系统输入或者请求系统输出某些事件来触发系统的执行。

- 参与者通常是人所担当的角色，但是也可能是任何类型的系统。

- 参与者和用户并非同一回事。一个典型的用户可能在使用系统时扮演了一系列不同的角色，而一个参与者表示了一类外部实体，它们仅扮演一种角色。

Tools

- Rational Software Architecture
- Rational Software Modeler
- Rational Rose
- Together
- Visual Paradigm
- StarUML
- Enterprise Architect

# Design Patterns

Acyclic Visitor

Dependency Injection

Inversion of Control

Null Object

Motostate

MVC

###### Head First Design Patterns

The Factory Method Pattern defines an interface for creating an object, but lets subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

The Singleton Pattern ensures a class has only one instance, and provides a global point of access to it.

A "template method" defines the steps of an algorithm, deferring to subclasses for the implementation of those steps.
The Template Method Pattern gives us an important technique for code reuse.
The template method's abstract class may define concrete methods, abstract methods and hooks.
Abstract methods are implemented by subclasses.
Hooks are methods that do nothing or default behavior in the abstract class, but may be overridden in the subclass.
To prevent subclasses from changing the algorithm in the template method, declare the tempalte method as final.
The hollywood Principle guides us to put decision-making in high-level modules that can decide how and when to call low level modules.
You'll see lots of uses of Template Method Pattern in real world code, but don't expect it all (like any pattern) to be designed "by the book".
The Strategy and Template Method Patterns both encapsulate algorithms, one by inheritance and one by composition.
The Factory Method is a specialization of Template Method.

An iterator allows access to an aggregate's elements without exposing its internal structure.
An iterator takes the job of iterating over an aggregate and encapsulates it in another object.
When using an iterator, we relieve the aggregate of the responsibility of supporting operations for traversing its data.
An iterator provides a common interface for traversing the items of an aggregate, allowing you to use polymorphism when writing code that makes use of the items of the aggregate.
We should strive to assign only one responsibility to each class.
The Composite Pattern provides a structure to hold both individual objects and composites.
The Composite Pattern allows clients to treat composites and individual objects uniformly.
A Component is any object in a Composite structure. Components may be other composites or leaf nodes.
There are many design tradeoffs in implementing Composite. You need to balance transparency and safety with your needs.

The State Pattern allows an object to have many different behaviors that are based on its internal state.
Unlike a procedural state machine, the State Pattern represents state as a full-blown class.
The Context gets its behavior by delegating to the current state object it is composed with.
By encapsulating each state into a class, we localize any changes that will need to be made.
The State and Strategy Patterns have the save class diagram, but they differ in intent.
Strategy Pattern typically configures Contact classes with a behavior or algorithm.
State Pattern allows a Context to change its behavior as the state of the Context changes.
State transitions can be controlled by teh State classes or by the Context classes.
Using the State Pattern will typically result in a greater number of classes in your design.
State classes may be shared among Context instances.
Think of the Strategy Pattern as a flexible alternative to subclassing.
Think of the State Pattern as an alternative to putting lots of conditionals in your context.

The proxy pattern provides a surrogate or placeholder for another object to control access to it.
The Proxy Pattern provides a representative for another object in order to control the client's access to it. There are a number of ways it can manage that access.
A remote proxy controls access to a remote object.
A virtual proxy controls access to a resource that is expensibe to create.
A protection proxy controls access to a resource based on access rights.
Many other variants of the Proxy Pattern exist including caching proxies, synchronization proxies, firewall proxies, copy-on-write proxies, and so on.
Proxy is structurally similar to Decorator, but the two differ in their purpose.
The Decorator Pattern adds behavior to an object, while a Proxy controls access.
Java's built-in support for Proxy can build a dynamic proxy class on demand and dispatch all calls on it ot a handler of your choosing.
Like any wrapper, proxies will increase the number of classes and objects in your designs.

The Model View Controller Pattern (MVC) is a compound pattern consisting of the Observer, Strategy and Composite patterns.
The model makes use of the Observer Pattern so that it can keep observers updated yet stay decoupled from them.
The controller is the strategy for the view. The view can use different implementations of the controller to get different behavior.
The view uses the Composite Pattern to implement the user interface, which usually consists of nested components like panels, frames and buttons.
