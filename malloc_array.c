#include<stdio.h>
#include <stdlib.h>
void defineArray(int ,int ,double **);
int main(void)
{
	int cols,rows;
	while(scanf("%d,%d",&cols,&rows)!=2)puts("Check input,please");
	double **array=malloc(rows*sizeof(double *)); 
    defineArray(rows,cols,array);
	for(int i=0;i<rows;++i){
		for(int j=0;j<cols;++j)
			printf("%f ",*(*(array+i)+j));
		putchar('\n');
	}
	free(array);
	return 0;
	
 } 
 
void defineArray(int rows,int cols,double **array)
 {
 	for(int i=0;i<rows;i++)
	{
		printf("please %d number and separate with space:\n",cols);
		array[i]=malloc(cols*sizeof(double));
		for(int j=0;j<cols;j++)
		scanf("%lf",(*(array+i)+j));
	}
 }
 