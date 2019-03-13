#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int  foo(char *);
int  foo(char *s){
    for(int i=0,j=strlen(s)-1;i<j;)if(s[i++]!=s[j--])return 0;
    return 1;
}

int main(void) {
    char ch[]="aaa000000000000000aaa";
    printf("%d",foo(ch));

}
