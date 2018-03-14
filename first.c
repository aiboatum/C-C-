#include <stdio.h>
#include <string.h>
#define NAME "GIGATHINK, INC."
#define ADDRESS "101 Megabuck Plaza"
#define PLACE "Megapolis,CA 94094"
#define WIDTH 40
#define SPACE ' '
void show_n_char(char, int);
int main(void) {
	printf("/");
    show_n_char('*', WIDTH);
	puts("");
    show_n_char(SPACE,(WIDTH-strlen(NAME))/2);
	printf("%s", NAME);
	putchar('\n');
	show_n_char(SPACE,(WIDTH-strlen(ADDRESS))/2);
    printf("%s\n",ADDRESS);
    show_n_char(SPACE,(WIDTH-strlen(PLACE))/2);
    //puts("");
    printf("%s\n",PLACE);
    printf("/");
    show_n_char('*',WIDTH);
    return 0;
}
void show_n_char(char ch,int n){
    for(int i=0;i<n;++i)
    putchar(ch);
}