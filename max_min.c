#include <stdio.h>
int foo(int ,int );
int foo(int a,int b){
    int r=a%b;
    while(r){
    //int r=a%b;
    a=b;
    b=r;
    r=a%b;
    }
return b;
}
int main(void){
    printf(" 128 and 56 :%d",foo(128,56));
}