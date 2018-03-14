#include <stdio.h>
#define showlist(...) puts(#__VA_ARGS__)
int main(void){
    showlist();
    return 0;
}