//该用例展示两级dereference的赋值不安全
#include <stdio.h>
//gcc compiler will give the warning :assignment from incompatible pointer type
//but it does work!(this is undefined behavior )
//may be ok!may be no ok! 
int main(void){
    const int **p2;
    int *p1;
    const int n=15;
    printf("p1 =%p\n",p1);
    printf("&n =%p\n",&n);
    p2=&p1;
    *p2=&n;
    *p1=10;
    printf("p1 =%p\n&n =%p",p1,&n);
   // printf("%p",*p2);
    return 0;
    
}
