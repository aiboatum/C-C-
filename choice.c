#include <stdio.h>
char get_choice(void);
void count(void);
char get_first(void);
int main(void){
    //get_choice();
    int choice;//the type 'int' can detect EOF
    while((choice=get_choice())!='q'){
    switch(choice){

    case 'a':printf("Buy low ,sell high.\n");
    break;
    case 'b':putchar('\a');
    break;
    case 'c':count();
    break;
    default:
    printf("Program error");
    break;
            }
    }
    puts("Bye~");
    return 0;
}
char get_choice(void){
    int ch;
printf("Enter the letter of your choice :\n");
puts("a.advice          b.bell");
puts("c.count           q.quit");
ch=get_first();
for(;(ch<'a'||ch>'c')&&ch!='q';){
printf("Please repond with a,b,c,or q.\n");
ch=get_first();}
return ch;
}
char get_first(void){
    int ch;
    //
    //for(;((ch=getchar())=='\n');)continue;//v1.0
    ch=getchar();//version 2.0
    for(;getchar()!='\n';)continue;
    return ch;
}
void count(void){
    int n,i;
    printf("Count how far ?Enter an integer :");
    for(;scanf("%d",&n)!=1;){
        char ch;
        putchar('$');
        while((ch=getchar())!='\n')putchar(ch);//note that (ch=getchar())
        //not the ch=getchar()
        //if that,it will put 1's ascii code 
        printf("$ is not an integer.\nPlease input an integer value:");
        scanf("%d",&n);
        }
    getchar();//version 2.0
    for(i=1;i<=n;++i)printf("%d\n",i);
}