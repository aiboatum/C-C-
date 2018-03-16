#include <stdio.h>
#include <string.h>
/***************
*   conversion of decimal to hex and octal
*   conversion of hex and octal to decimal
***************/


/************************
 * 十六进制转十进制和十进制转十六进制其实和atoi和itao思想一样
 ***********************/ 
char * detohex(int value,char *);
long hextode(char *);
int find(char *,char );//查找数组下标
long octtode(long );
long detooct(int );
long pow10_(int);
long pow10_(int i){
    long result=1;
    while(i--){
        result*=10;
    }
    return result;
}
long detooct(int  n){
    long ans=0;
    int count=0;
    while(n){
        long x=n&0x7;
        ans+=x*pow10_(count);
        count++;
        n>>=3;
    }
    return ans;
}
long octtode(long n){
    
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
        n[i]=value&0xf;//取出低四位,namely value%16(0xf is 00001111"In 8bits")
        value>>=4;//左移四位,即value除以16更新。
        /*类比十进制e.g. 123/10，可以得到12.
        123%10可以得到3，即最低位的数字。
        同理，十六进制mod 16（即上面的value&0xff）可以得到最低位
        */
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
// int main(void)
//     {//此方法实现思想和detohex一样，每位储存起来
//         int num,i,len=0,x[100];
//         // printf("enter a number\t");
//         // scanf("%d",&num);
//         while (num>0){
//             x[len++]=num&0x7;//
//             num=num>>3;
//         }
//         for(i=len-1;i>=0;i--)
//             printf("%d",x[i]);
//         return 0;
//    }
int main(void){
    char ch[32];
    //printf("%d\n",sizeof(long long));
    printf("%d\n",hextode("fffffff"));
    printf("%s\n",detohex(268435455,ch));
    printf("%ld\n",detooct(10));
}