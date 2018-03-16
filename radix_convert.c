#include <stdio.h>
#include <string.h>
char * detohex(int value,char *);
long hextode(char *);
int find(char *,char );
long octtode(char *);
long octtode(char *){
    char octmap[]="01234567";
}
int find(char *s,char ch){
    for(int i=0;i<strlen(s)-1;++i){
        if(ch==s[i])return i;
    }
}
char *detohex(int value,char *result){
    char hexmap[]="0123456789ABCDEF";
    int n[8];
    int w=sizeof(int)<<3;
    w>>=2;
    for(int i=0;i<w;i++){//假设32bit representation
        n[i]=value&0xf;//取出低四位
        value>>=4;//左移四位
    }//32bit，n[0]储存最低四位
    for(int i=7;i>=0;i--)
        result[7-i]=hexmap[n[i]];
        result[8]='\0';
    return result;
}
long  hextode(char *s){
        char hexmap[]="0123456789ABCDEF";
        long result =0;
        int shift=0;
        for(int i=strlen(s)-1;i>=0;i--){
            int d=find(hexmap,s[i]);
            result+=(d<<shift);//left-shift 0bit is equivalent to multiply by 16^0
            //left-shift 4bits by 16^1,8bits by 16^2,etc.
            shift+=4;
        }
        return result;
}
int main(void){
    char ch[32];
    //printf("%d\n",sizeof(long long));
    printf("%d\n",hextode("fffffff"));
    printf("%s\n",detohex(268435455,ch));
}