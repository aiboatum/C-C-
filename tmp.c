#include<string.h>
#include<stdio.h>
int getSum(int a, int b) {
    return b ? getSum(a^b,(a&b)<<1) :a;
}
int main(void)
{
    printf("%d",getSum(1,2));
    return 0;
}
