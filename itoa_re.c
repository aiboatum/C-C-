//递归实现int到char*
#include <stdio.h>
#include <stdlib.h>
#define ABS(x) (x)>0?(x):-(x)
/***************************
 * 以下单重指针实现不能正确完成功能 
 * 参数中p的值没有改变
 * 改用双重指针
 * *************************/
void itoa_recurssive(int ,char **);
void itoa_recurssive(int n,char **p) {//行参应该传入指针的地址
	const char digit[] = "0123456789";
	if (n<0) {
		**p='-';
        (*p)++;
		n=ABS(n);
	}
    if(n/10){//if(n<10)递归终止条件(出口)
    itoa_recurssive(n/10,p);
    (*p)++;
    }
	**p=(digit[n%10]);
    return ;
}
int main(void) {
    char ch[32];
    char *t=ch;
	itoa_recurssive(-2147483647,&t);
	*++t='\0';
    puts(ch);
  
}