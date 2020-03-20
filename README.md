## effective c++

### 一 ，让自己习惯C++

#### 条款01：视C++为一个语言联邦

1. C
   
   * 说到底C++仍是以c为基础；

2. Object-Oriented C++
   
   * classes（包含构造函数和析构函数）、封装、继承、多态、virtual函数（动态绑定）....等等；

3. Template C++
   
   * 这是C++的泛型编程部分，实际上由于templates威力强大，它们带来崭新的编程泛型；

4. STL
   
   * STL是个template程序库；

**记住这四个次语言，当你从某个次语言切换到另一个，导致高效编程守则要求你改变策略时，不要感到惊讶。**

#### 条款02：尽量以const、enum、inline替换#define

1. 使用常量替换宏定义，如下:
   
   ```cpp
   #define ASPECT_RATIO 1.653
   //替换为如下
   const double AspectRatio = 1.653; // 使用次常量替换上面的宏定义 ,大写名称通常用于宏，
   
   II 因此这里改变名称写法。
   const char* const authorName = "ilong";
   const std::string authorName("ilong");
   ```

2. 使用枚举替换宏定义，如下：
   
   ```cpp
   #define NumTurns 5
   int scores[NumTurns];
   //替换为如下
   enum {NumTurns = 5};
   int scores[NumTurns];
   ```

3. 使用inline替换宏函数，如下：
   
   ```cpp
   // 以 a 和 b 的较大值调用 f
   
   #define CALL WITH MAX (a, b) f ((a) > (b) ? (a) : (b))
   
   /*
   无论何时当你写出这种宏，你必须记住为宏中的所有实参加上小括号，否则某
   
   些人在表达式中调用这个宏时可能会遭遇麻烦。但纵使你为所有实参加上小括号，
   
   看看下面不可思议的事情:
   */
   
   int a = 5, b = 0;
   CALL_WITH_MAX(++a, b); // 被累加二次
   
   CALL_WITH_MAX(++a, b+l0); // 被累加一次
   ```
   
   //替换为下面的方式
   template<typename T>
   
   inline int callWithMax(const T& a , const T& b){
      return a > b ? a : b;
   } 

```

**请记住:  
·对于单纯常量，最好以 canst 对象或 enums 替换 #defineso  。
·对于形似函数的宏 (macros) ，最好改用 inline 函数替换 #defines 。**

#### 条款03：尽可能使用const

1. const常用法，如下：

   ```cpp
   char greeting[] = "hello";
   char* p = greeting; //non-const pointer, non-const data
   const char* p = greeting; //non-const pointer, const data
   char* const p = greeting; //const pointer, non-const data
   const char* const p = greeting; //const pointer, const data
```

* const 语法虽然变化多端，但并不莫测高深。如果关键字 const 出现在星号左
  边，表示被指物是常量:如果出现在星号右边，表示指针自身是常量:如果出现在
  星号两边，表示被指物和指针两者都是常量。

* 如果被指物是常量，有些程序员会将关键字 const 写在类型之前，有些人会把
  它写在类型之后、星号之前。两种写法的意义相同，所以下列两个函数接受的参数
  类型是一样的，如下：
  
  ```
  void f1(const Widget* pw);
  void f2(Widget const * pw);
  ```
2. STL迭代器使用const：
   
   STL 选代器系以指针为根据塑模出来，所以迭代器的作用就像个?指针。声
   明选代器为 const就像声明指针为 const一样(即声明一个T* const 指针) ，表
   示这个迭代器不得指向不同的东西，但它所指的东西的值是可以改动的。如果你希
   望迭代器所指的东西不可被改动(即希望STL 模拟一个 const T* 指针) ，你需要
   的是 const_iterator:
   
   ```cpp
   std::vector<int> vec;
   const std::vector<int>::iterator_iter = vec.begin(); //iter 的作用像个 T* const
   
   *iter = 10;       //没问题，改变 iter 所指物
   
   ++iter;           //错误! iter 是const
   ```
   
   std::vector<int>::const_iterator clter = vec.begin(); //clter 的作用像个 const T*
   
   *clter = 10;      //错误! *clter 是const
   
   ++clter;          // 没问题，改变 clter

```

3. const 成员函数

   将 const 实施于成员函数的目的，是为了确认该成员函数可作用于 const 对象
   身上。这一类成员函数之所以重要，基于两个理由。第一，它们使 class 接口比较
   容易被理解。这是因为，得知哪个函数可以改动对象内容而哪个函数不行，很是重
   要。第二，它们使"操作 const 对象"成为可能。这对编写高效代码是个关键，因
   为如条款 20 所言，改善 C++ 程序效率的一个根本办法是以 pass by
   reference-to-const 方式传递对象，而此技术可行的前提是，我们有const 成员函数
   可用来处理取得(并经修饰而成)的canst对象。

   ```cpp
   class TextBlock {
   public:
      const char& operator[] (std::size t position) const // operator[] for const 对象
       { return text[position]; )
       char& operator[] (std::size_t position) // operator [] for non-const 对象
       { return text[position]; )
    private:
       std::string text;
    };
     //TextBlock 的 operator[] 可被这么使用:
    TextBlock tb ("Hello") ;
    std::cout<< tb[O] <<std::endl; //调用 non-const TextBlock::operator[]
    const TextBlock ctb("World");
    std::cout<< ctb[O] <<std::endl; //调用 const TextBlock::operator[]
```

   在 const 和 non-const成员函数中避免重复，mutable 是个解决办法；

```cpp
   class CTextBlock {
   public:
       std::size_t length() const;

   private:
       char *pText;
       mutable std::size_t textLength; //这些成员变量可能总

       mutable bool lengthIsValid;     //会被更改，即使在

   };                                  //const成员函数内。

   std::size_t CTextBlock::length() const {
       if (!lengthIsValid) {
           textLength = std::strlen(pText); //现在，可以这样，

           lengthIsValid = true;            //也可以这样。

       }
       return textLength;
   }
```

**请记住  
·将某些东西声明为 const 可帮助编译器侦测出错误用法。 const 可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体。  
·编译器强制实施 bitwise constness ，但你编写程序时应该使用"概念上的常量性"(conceptual constness) 。  
·当 const 和 non-const 成员函数有着实质等价的实现时，令 non-const 版本调用 const 版本可避免代码重复。**

#### 条款04：确定对象被使用前已先被初始化

1. 区分赋值和初始化
   
   ```cpp
   class ABEntry { //ABEntry = "AddressBook Entry"
   public:
       ABEntry(const std::string &name, const std::string &address,
               const std::list<PhoneNumber> &phones);
   
   private:
       std::string theName;
       std::string theAddress;
       std::list<PhoneNumber> thePhones;
       int numTimesConsulted;
   }
   
   ABEntry::ABEntry(const std::string& name, 
                    const std::string& address,
                     const std::list<PhoneNumber>& phones){
       theName = name;        //这些都是赋值 (assignments) ,
   
       theAddress = address;  //而非初始化 (initializations)。
   
       thePhones = phones;
       numTimesConsulted= 0;
   };
   
   //ABEntry 构造函数的一个较佳写法是，使用所谓的 member initialization list (成员初值列〉替换赋值动作:
   ABEntry::ABEntry(const std::string& name,
                    const std::string& address,
                    const std::list<PhoneNumber>& phones)
   :theNarne(narne),
   theAddress(address), //现在这些都是初始化 (initializations)
   thePhones(phones),
   numTimesConsu1ted(O)
   { }  //现在构造函数本体不必有任何动作
   ```

2. 使用单例
   
   ```cpp
   // .h
   #include <stdio.h>
   #include <mutex>
   #include <memory>
   
   template <class T>
   class Singleton final {
   
   public:
      Singleton() = delete;
      
      static T* instance(){
         std::call_once(mOnce, [&](){
            mInstance.reset(new T());
         });
         return mInstance.get();
      }
   
      Singleton(const Singleton&) = delete;//禁用copy方法
      const Singleton& operator=( const Singleton&) = delete;//禁用赋值方法
   
   private:
      static std::once_flag mOnce;
      static std::unique_ptr<T> mInstance;
   };
   
   //.cpp
   template <class T>
   std::once_flag Singleton<T>::mOnce;
   
   template <class T>
   std::unique_ptr<T> Singleton<T>::mInstance;
   
   //Instructions for use
   Foo * foo = Singleton<Foo>::Instance();
   ```

**请记住  
·为内置型对象进行手工初始化，因为 C++不保证初始化它们。  
·构造函数最好使用成员初值列 (member initialization list) ，而不要在构造函数本体内使用赋值操作(assignment) 。初值列列出的成员变量，其排列次序应该和它们在 class 中的声明次序相同。  
·为免除"跨编译单元之初始化次序"问题，请以local static 对象替换 non-local  static 对象。**

### 二，构造/析构/赋值运算
