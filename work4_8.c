#include <stdio.h>
#define SIZE 40
int main(void){
    char surname[SIZE];
    char lastname[SIZE];
    printf("Enter your surname :\n");
    while(scanf("%s",surname)!=1)printf("Enter the corrct surname,Please");
    puts("Enter your last name:");
    while(scanf("%s",lastname)!=1)printf("Enter the correct lastname,Please");
    char ch;
    for(int i=0;(ch=surname[i])!='\0';i++)
    putchar(ch);
    printf(" ");
    //putchar('\t');
    int i=0;
    while(lastname[i]!='\0')
    {putchar(lastname[i]);++i;}
    return  0;

}