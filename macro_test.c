#include <stdio.h>
#define showlist(...) puts(#__VA_ARGS__)
int main(void){
    showlist("Hello!");
    showlist(hello);
    return 0;
}