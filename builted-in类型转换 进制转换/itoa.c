#include <stdio.h>
#include <stdlib.h>
// itoa定义在stdlib.h中
// 函数原型： char * myitoa(int value,char *str,int base);

char * myitoa(int value,char *str,int base){
    const char index[]="0123456789ABCDEF";

    unsigned unum;/*中间变量*/
    int i=0,j,k;
    /*确定unum的值*/
    if(base==10&&value<0)/*十进制负数*/
    {
        unum=(unsigned)-value;  // abs 等价于 (~a+1)
        str[i++]='-';
    }
    else unum=(unsigned)value;/*其他情况*/
    /*转换*/
    do{
        str[i++]=index[unum%(unsigned)base];
        unum/=base;
    }while(unum);

    // 添加尾段'\0'
    str[i]='\0';

    // reverse 
    k=(str[0]=='-')?1:0;
    for(j=k;j<=(i-1)/2;j++)
    {   char temp;
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
    return str;
}
int main(void){
    char str[100];
    printf("%s\n",myitoa(INT_MIN,str,2));
    printf("%s\n",myitoa(INT_MAX,str,2));

    printf("%s\n",itoa(INT_MIN,str,2));
    printf("%s\n",itoa(INT_MAX,str,2));
}
