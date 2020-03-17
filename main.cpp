#include <iostream>
#include "CTextBlock.h"

template <typename T>
inline T callWithMax(const T& a, const T& b){
    return a > b ? a:b;
}

void f1(const int * pw);
void f2(int const * pw); // 两种定义的效果一下，都表示pw是一个常量

int main() {
    std::cout << "Hello, World!" << std::endl;
    int a = 11;
    std::cout << "max: " << callWithMax(++a, 13) << std::endl;

    const CTextBlock textBlock("abcd");
    char* pc = &textBlock[1];
    std::cout<< "pc: " << pc << std::endl;

    std::cout << "textBlock[0]:" << textBlock[0] << std::endl;

    return 0;
}
