#include <stdio.h>
int main(void){
   void swap(int *,int *);
   int a=5,b=4;
   printf("%d , %d",a,b);
   swap(&a,&b);
    printf("%d , %d",a,b);
    return 0;
}
void swap(int * a,int * b){
    int tem;
    tem=*a;
    *a=*b;
    *b=tem;
}