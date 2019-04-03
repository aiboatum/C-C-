// #include <cstdio>
// int cnt=0;
// void foo(int n,int r,int ld,int rd){
//     if(r==(1<<n)-1){
//         ++cnt;
//         return;
//     }
//     int D=((1<<n)-1)&(~(r|ld|rd));
//     while(D){
//         int bit=D&(~D+1);
//         D=D^bit;
//         foo(n,r|bit,(bit|ld)<<1,(rd|bit)>>1);
//     }
// }
// int main(){
//     foo(15,0,0,0);
//     printf("%d",cnt);
// }
#include <stdio.h>
int count = 0;
void try(int n,int A, int B, int C){
        for(int bit,D = ((1<<n)-1) & (~(A|B|C));B!=((1<<n)-1)&& D!=0; bit=D&(~D+1),D=D^bit, try(n,(A|bit)<<1, B|bit, (C|bit)>>1));
        count=(B==(1<<n)-1)?(count+1):count;
}
int main(){
    try(15,0, 0, 0);
    printf("%d\n", count);
}