#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Words{
        char s[30];
        int count;
}Words;
//单词间隔以空格 制表符 标点符号等'\n'不单独作为间隔，
char * fscanf(FILE *);//返回单词
char * fscanf(FILE * p){
        char ch;
        int n=0;
        while(isalpha(ch=getc(p))){
        ++n;
        }
        CHAR 
}
int main(void){
FILE *pfile=fopen("test.txt","r");
if(!pfile){puts("Error occurs!");exit(1);}
char *s[128]={NULL};
char ch;
while(isalpha(ch=getc(pfile))){

}
}