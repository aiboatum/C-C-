#include <stdio.h>
int *foo(void);
//int i[3];//global varaible is stored in the heap;
int *foo(void){
  static  int i[3];//Note:the lifetime ,in program, of static variable 
for(int j=0;j<3;++j)
i[j]=j*2+1;
return i;
}
int main(void){
   
    int *num=foo();
    for(int i=0;i<3;++i)printf("%d\n",*(num+i));
    return 0;
}