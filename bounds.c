// bounds.c
#include <stdio.h>
#define SIZE 4
int main(void){
    int value1=44;
    int arr[SIZE];//index 0~3
    int value2=88;
    printf("value1 =%2d,value2 =%2d\n",value1,value2);
    for(int i=-1;i<=SIZE;++i)arr[i]=2*i+1;//-1~3
    for(int i=-1;i<7;++i)printf("%2d arr[%d]:%2d\n",i,i,arr[i]);
    printf("vlaue1 = %d,value2 = %d\n",value1,value2);
    for(int i=-1;i<7;++i)
    printf("address of arr[%d]:%p\n",i,&arr[i]);
    //printf("address of arr[4] :%p\n",&arr[4]);
    printf("address of value1 :%p\n",&value1);
    printf("address of value2 :%p\n",&value2);
    return 0;
}