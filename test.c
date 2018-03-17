#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct Words{
        char s[100];
        int n;//单词长度
}Words;
int foo_1(char *,int *);
int foo_1(char *s,int *n){
        int ch;
        while(!isalpha(ch=getc(stdin))&&ch!='\n')
        continue;
        *s=ch;
        int i=1;
        while(isalpha(ch=getc(stdin))&&ch!='\n'){
        s[i++]=ch;
        }
        s[i]='\0';
        *n=i;
        if(ch=='\n')return 0;
        else return 1 ;
}
int main(void){
struct Words s={{s.n=0}};
int n;
char temp[100];
printf("%d  %d\n",foo_1(temp,&n),n);
// char temp[100];
// int n;
// while(foo_1(temp,&n)!=0){
//         printf("%d\n",n);
//         if(s.n<n){
//                 strcpy(s.s,temp);
//                 s.n=n;
//         }
//         else continue;
// }
// printf("%s : %d",s.s,s.n);
}