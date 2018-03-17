#include <stdio.h>//利用fscanf和fprintf函数完成此功能
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct Words{
        char s[30];
        int count;
        int tag;//标志该结构体是否已被使用
}Words;
int f_scanf(FILE *,char *);
int f_scanf(FILE *p,char *ch){
        int c;
        while(!isalpha(c=getc(p))&&c!=EOF)
        continue;//排除开头非字母
        ch[0]=c;
        int i=1;
        while(isalpha(c=getc(p))&&c!=EOF){
        ch[i++]=c;
        }
        ch[i]='\0';
        if(c==EOF)return 0;
        else return 1;
}
int main(void){
        struct Words s[1000]={{.count=0,.tag=0}};
        FILE *p;
        p=fopen("test.txt","r");
        if(!p){
                puts("Error occurs!!");
                exit(1);
        }
        char temp[30];       
        while(f_scanf(p,temp)==1){
                   for(int i=0;i<1000;++i){
                        if(s[i].tag==0){
                        strcpy(s[i].s,temp);  
                        s[i].tag=1;
                        s[i].count++;
                        break;
                        }
                        else if(strcmp(temp,s[i].s)==0){
                        s[i].count++;
                        break;
                        }
                }
        }//从中file中读取一个单词放入s结构体的char s[30]中 
        fclose(p);
        for(int i=0;s[i].tag;i++)
        printf("%s : %d\n",s[i].s,s[i].count);
}