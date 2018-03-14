#include <stdio.h>
 //int test=9;//这是global variable 具有file scope with external linkage
 //这是一个定义
//char *s_gets(char *st,int n);
#include "s_gets.h"
char *s_gets(char *st,int n){
    char *ret_val;
    int i=0;
    ret_val=fgets(st,n,stdin);
    if(ret_val){
        while(st[i]!='\n'&&st[i]!='\0')++i;
        if(st[i]=='\n')
        st[i]='\0';
        else
        while(getchar()!='\n')
        continue;

    }
    return ret_val;
}