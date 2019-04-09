#include <stdio.h>
#include <stdlib.h>
char * itoa_(int n,char *b);
char * itoa_(int n,char *b){
    char *p=b;
    const char digit[]="0123456789";
    if(n<0){
        *p++='-';
        n*=-1;
    }
    int shifter=n;
    do{//Move to where representation end
        ++p;
        shifter/=10;
    }while(shifter);
    *p='\0';
do{//Move back
*--p=digit[n%10];//取个位上的数字
n/=10;
}while(n);
return b;
}
int main(void){
    char ch[30];
    char *t=ch;
    itoa_(12343,ch);
    for(;(*t);++t)
    putchar(*t);
    //printf("%s",itoa(12783,ch,10));
}
