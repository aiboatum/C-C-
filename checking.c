#include <stdio.h>
#include <stdbool.h>
int main(void){
long get_long(void);
bool bad_limits(long ,long,long ,long);
double sum_squres(long ,long);
const long MIN=-1E8L;
const long MAX=+1E8L;
long start,stop;
double answer;
printf("This is a program computes the sum of the squares of "
"integers in a range.\n"
"The lower bound should not be less than -1e+8 and \n"
"the upper bound should not be more than +1e+8.\n"
"Enter the limits (enter 0 for both limits to quit):\n"
"lower limit:");
start=get_long();
printf("upper limit:");
stop=get_long();
while(start!=0||stop!=0){
    if(bad_limits(start,stop,MIN,MAX))printf("Pleartry again\n");
else{

    answer=sum_squres(start,stop);
    printf("The sum of the squares of the integers from %ld to %ld is %g "
    "\n",start,stop,answer);

}
printf("Enter the limits (enter 0 for both limits to quit):\n");
printf("lower limits: ");
start=get_long();
printf("upper limits: ");
stop=get_long();
}
printf("done!\n");
return 0;

}
long get_long(void){
    long input;char ch;
    for(;scanf("%ld",&input)!=1;){
        putchar('\'');
    for(;(ch=getchar())!='\n';)putchar(ch);
    printf("\' is not an integer .\n Please enter an ");
    printf("integer value ,such as 23,34,or 3:");
    }
    return input;

}
double sum_squres(long a,long b){
    double total=0.0;
    for(long i=a;i<=b;i++){total+=(double)i*(double)i;}
    return total;
}
bool bad_limits(long begin,long end,long low ,long high){
    _Bool not_good=false;
    if(begin>end){
        printf("%ld isn't smaller than %ld .\n",begin,end);
        not_good=true;
    }
    if(begin<low||end<low){
        printf("Values must be %ld .\n ",begin,end);
        not_good=true;
    }
    if(begin>high||end>high){
        printf("Values must be %ld or less .\n ",high);
        not_good=true;
    }
    return not_good;
}