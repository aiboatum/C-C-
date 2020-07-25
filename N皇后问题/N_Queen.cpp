#include <cstdio>
// 使用位运算实现N皇后问题
// refer: http://www.matrix67.com/blog/archives/266
// #include <stdio.h>
// int cnt=0;
// void foo(int n,int r,int ld,int rd){
//     if(r==(1<<n)-1){
//         ++cnt;
//         return;
//     }
//     int D=((1<<n)-1)&(~(r|ld|rd));// 由于参数是int类型，
//                                   // 因此需要~(r|ld|rd)需要&(1<<n)-1即只保留后nbit
//     // int D=~(r|ld|rd);    // 如果参数是unsigned int，此时可以用这个
//     while(D){
//         int bit=D&(~D+1);
//         D=D^bit;
//         foo(n,r|bit,(bit|ld)<<1,(rd|bit)>>1);
//     }
// }

int count = 0;
void bar(int n,int A, int B, int C){
        for(int bit,D = ((1<<n)-1) & (~(A|B|C));B!=((1<<n)-1)&& D!=0; bit=D&(~D+1),D=D^bit, bar(n,(A|bit)<<1, B|bit, (C|bit)>>1));
        count=(B==(1<<n)-1)?(count+1):count;
}
int main(){
    bar(8,0, 0, 0);
    printf("%d\n", count);
}