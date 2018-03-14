#include <stdio.h>
#define ANSWER "Grant"
#define SIZE 40
extern int test;//这是一个test的声明，不是定义
//定义在s_gets中
char *s_gets(char *,int );
int main(void){
    char try[SIZE];
    printf("%d\n",test);
    puts("Who is buried iin Grant's tomb?");
    s_gets(try,SIZE);
    while(try!=ANSWER){
        puts("No,that's wrong.Try again.");
        s_gets(try,SIZE);
    }
    
    puts("That's right!");
    return 0;
}