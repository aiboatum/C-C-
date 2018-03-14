/*+++++++++++++++++++++++++++++++++++++++
+ 
+
+
+
+++++++++++++++++++++++++++++++++++++++*/
#include <stdio.h>
#define MONTHS 12
#define YEARS 5
int main(void){
    const float rain[YEARS][MONTHS]={
        (4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0,4.3,4.3,4.3,0.3),
        (4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0),
        (4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0),
        (4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0), 
        (4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0,4.3,4.3,4.3,3.0)

    };
    int years,month;
    float subto,total;
    printf(" YEAR   RAINFALL(inches)\n");
    for(years=0,total=0;years<YEARS;years++){
        for(month=0,subto=0;month<MONTHS;month++)
        subto+=rain[years][month];
        printf("%5d %10.1f\n",2010+years,subto);
        total+=subto;
    }
    putchar('\n');
    return 0;
}