#include <stdio.h>
int main(void) {
	int guess = 1;
	printf("Pick an integer from 1 to 100 .I will try guess it.\n");
	printf("Respond with a y if my guess is right and with \n an n if it is wrong.\n");
	printf("Uh...is your number %d?\n", guess);
	char ch;
	while ((ch=getchar()) != 'y') { 
		if(ch!='n')printf("you should input n or no or no way \n");
		else
		printf("Well ,then is it %d ?\n", ++guess); 
	while (getchar() != '\n')continue;
	}
	printf("I knew you could do it!\n");
	return 0;
}