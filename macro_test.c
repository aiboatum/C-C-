/***************************
 *  C语言Macro的高级用法
 *  update:2020/7/17
 **************************/

#include <stdio.h>
// #: "字符串化"处理，预处理器会把参数转换为字符数组
// 可以通过查看其扩展后的形式，来体会其是如何扩展的
#define ERROR_LOG(error_info) fprintf(stderr,"error: "#error_info"\n") 
#define print(...) puts(#__VA_ARGS__)


// ##: 字符串concatenate
// 123##456 -> 123456 
// 拼接后的类型与拼接的类型应相符合
#define Cat(X,Y) X##Y

// 高级用法，其中typeof是gcc特性
// (void)(&_x==&_y)：消除编译器比较不用类型_x,_y比较给出的警告
// 以下写法包含ggc特性，其它编译器可能无法通过编译
#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

int main(void){
    print("Hello!"); // puts("\"Hello!\"")
    print(hello, world);
    ERROR_LOG("error occurs!");

    printf("%d\n",Cat(123,456));

    // printf("%d",max(1,2));
    return 0;
}