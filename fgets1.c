#include <stdio.h>
#define STLEN 10
int main(void){
    char words[STLEN];
    int i;
    puts("Enter a string,please.(empty line to quit)");
    while(fgets(words,STLEN,stdin)!=NULL&&words[0]!='\n'){
        i=0;
        while(words[i]!='\n'&&words[i]!='\0')++i;
        if(words[i]=='\n')
        words[i]='\0';
        else 
        while(getchar()!='\n')
        continue;
        puts(words);

    }
   // fputs(words,stdout);
    puts("Done!");
    
    //char *c=fgets(words,STLEN,stdin);

    //printf("c = %10p\n",c);
    //printf("words = %10p\n",words);
    //printf("Your string twice (puts(),then fputs()):\n");
    //puts(words);
    //fputs(words,stdout);
    return 0;

}