#include <stdio.h>
#include <ctype.h>
int is_legal(const char *s);
int isoperator(char );
typedef struct stack{
    char ch[100];
    int top;
}Stack;
int isoperator(char ch){
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/')return 1;
    return 0;
}
int is_legal(const char *str){
    struct stack s={s.top=-1};
    while(*str){
       // putchar(*str);
        switch(*str){
        case '(':
                if(*++str=='\0')return 0;
                if(isoperator(*++str))return 0;
                s.ch[++s.top]='(';
                str++;
                continue;
        case ')':
                if(s.top==-1)return 0;
                if(s.ch[s.top]!='(')return 0;
                s.top--;
                str++;
                continue;
        case '+':
        case '-':
        case '*':
        case '/':if(*++str=='\0')return 0;
                if(*++str==')')return 0;
                if(isoperator(*++str))return 0;
                str++;
                continue;
        default:
        str++;
        continue;
        }
    }
    //printf("%c %d",s.ch[0],s.top);
    return 1;
   
}

int main(void){
    char s[]="1+2-34-4233";
    printf("%d",is_legal(s));
    
}