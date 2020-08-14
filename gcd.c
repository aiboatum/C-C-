#include <stdio.h>
/**
 *      辗转相除法
 */
int foo(int ,int );
int gcd(int ,int);
int foo(int a,int b){
    if (b==0||a==0)return a|b;
    for(int r=a%b;r;a=b,b=r,r=a%b);
    return b;
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int main(void){
    printf("gcd(128,56)=%d\n",gcd(128,56));
    printf("gcd(128,56)=%d\n",foo(128,56));
}