#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTILE 40
#define MAXAUTO 40
#define MAXBKS 10 //最大书籍数量
char * s_gets(char *,int );
struct book{
    char title[MAXTILE];
    char author[MAXAUTO];
    float value;
};
int main(void){
    struct book lib[MAXBKS];
    int count=0;
    FILE * pbooks;
    if((pbooks=fopen("book.dat","a+b"))==NULL){fputs("Can't open book.dat file\n",stderr);exit(1);}
    rewind(pbooks);
    while(count<MAXBKS&&fread(&lib[count],sizeof(struct book),1,pbooks)==1);
    {
        if(0==count)puts("Current contents of book.dat");
        printf("%s by %s : $%.2f\n",lib[count].title,lib[count].author,lib[count].value);
        count++;
    }
    int filecount=count;
    if(count==MAXBKS){fputs("The book.dat file is full.",stderr);exit(2);}
    puts("Please add new book titles.");
    puts("Press [enter] at the start of a line to stop.");
    while(count<MAXBKS&&s_gets(lib[count].title,MAXTILE)!=NULL)&&lib[count].title[0]!='\0'){
        puts("Now enter the author.");
        s_gets(lib[count].author,MAXAUTO);
        PUTS("Now enter the value.");
        scanf("%f",&lib[count++].value);
        while(getchar()!='\n')continue;//清理输入行
        if(count<MAXBKS)puts("Enter the next title.");
    }
    if(count>0){
        puts("Here is the list of your books:");
        for(int index=0;index<count;++index)
        printf("%s by %s :$%.2f\n",lib[index].title,lib[index].author,lib[index].value);
        fwrite("")
    }
}