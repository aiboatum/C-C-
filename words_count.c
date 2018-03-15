#include <stdio.h>//利用fscanf和fprintf函数完成此功能
//fscanf和fprintf sscanf 和 sprintf 更加灵活
#include <string.h>
#include <stdlib.h>
typedef struct Words{
        char s[30];
        int count;
        int tag;
}Words;
// int f_scanf(FILE *,char *);
// int f_scanf(FILE *p,char *ch){
//     fscanf(p,"%s",ch);
//     char *t=ch;
//     while(*t){
//             if()
//     }    
// }
int main(void){
        struct Words s[1000]={{.count=0,.tag=0}};
        FILE *p;
        p=fopen("test.txt","r");
        if(!p){
                puts("Error occurs!!");
                exit(1);
        }
       
        //int i=0;
        char temp[30];       
        while((fscanf(p,"%s",temp)==1)){
                   for(int i=0;i<1000;++i){
                        if(s[i].tag==0){
                        strcpy(s[i].s,temp);  
                        s[i].tag=1;
                        s[i].count++;
                        break;
                        }
                        else if(strcmp(temp,s[i].s)==0)
                        {s[i].count++;break;}
                   
                //fprintf(stdout,"%s\t",s[i].s);
                }
                
        }//从中file中读取一个单词放入s结构体的char s[30]中 
        fclose(p);
        for(int i=0;s[i].tag;i++)
        printf("%s : %d\n",s[i].s,s[i].count);
}