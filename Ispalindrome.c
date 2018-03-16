#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int  foo(char *);
int  foo(char *s){
    int n=strlen(s)-1;
    char *p1=s,*p2=s+n;
    while(p1<=p2){
        if(*p1!=*p2)return 0;
        p1++;
        p2--;
    }
    return 1;
}

int main(void) {
    char ch[]="aaa000000000000000aaa";

    printf("%d",foo(ch));

}