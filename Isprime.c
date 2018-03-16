#include <stdio.h>
#include <math.h>//sqrt函数
int ISprime_1(int );
int ISprime_2(int );
int ISprime_3(int );
int ISprime_1(int n){
    for(int i=2;i<=n/2;i++)
    if(n%i==0)return 0;//1%2等于0
    return 1;
}
//一个数若可以进行因数分解，那么分解时得到的两个数一定是一个小于等于sqrt(n)，一个大于等于sqrt(n)，
int ISprime_2(int n){
    if(n<2)return 0;
    if(n==2)return 1;//2 is prime
    for(int i=2;i<=sqrt(n);++i)//for(int i=0;i*i<=n;++i)
    if(n%i==0)return 0;
    return 1;
}
//改进
int ISprime_3(int n){
    if(n<2)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    for(int i=3;i*i<=n;i+=2)
    if(n%2==0)return 0
    return 1;
}

int main(void){

}