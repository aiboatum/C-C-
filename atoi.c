#include <stdio.h>
#include <string.h>
int  atoi(char *);
int  atoi(char *s){
    int num=0;
    int tag=1;
    if(*s=='-'){
        tag=-1;
        s++;
    }
    for(int i=0;i<strlen(s);i++)
        {
            num=num*10+(s[i]-'0');
        }
    return num*tag;
}
int main(void){
    char s[]="-123456";
    printf("%d",atoi(s));
}
