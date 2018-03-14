#include <stdio.h>
#include <limits.h>//提供char_bit定义,number of bits in a char,该系统为8
char *itobs(int ,char *);//integer to binary string
void show_bstr(const char *);
int main(void){
    char bin_str[CHAR_BIT * sizeof(int)+1];
    int number;
    puts("Enter integers and see them in binary.");
    puts("Non-numeric input terminates program.");
    while(scanf("%d",&number)==1){
        itobs(number,bit_str);
        show_bstr(bin_str);
        putchar('\n');
    }
    puts("Bye!");
}
char * itobs(int n,char * ps){
    int i;
    const static int size =CHAR_BIT*sizeof(int);
    for(i=size-1;i>=0;i--,n>>i)
    ps[i]=(01&n)+'0';
}