#include <stdio.h>
#include <limits.h>//提供char_bit定义,number of bits in a char,该系统为8
void itobs(int ,char *);//integer to binary string
void show_bstr(const char *);
int main(void){
    char bin_str[CHAR_BIT * sizeof(int)];
    int number;
    puts("Enter integers and see them in binary.");
    puts("Non-numeric input will terminate program.");
    while(scanf("%d",&number)==1){
        itobs(number,bin_str);
        show_bstr(bin_str);
        putchar('\n');
    }
    puts("Bye!");
}
void itobs(int n,char * ps){
    const static int size =CHAR_BIT*sizeof(int);
    for(int i=0;i<size;++i)
    ps[size-1-i]=(0x1&(n>>i))+'0';
}
void show_bstr(const char *s){
    for(int i=0;i<CHAR_BIT * sizeof(int);++i){
        printf("%c",s[i]);
    }
}