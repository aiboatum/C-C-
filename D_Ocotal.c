/*十进制转化为八进制*/
int main(void){
int y = 8;
int decimal = 230;
char base4Answer[32];
int firstDigit;
int secondDigit;
if(y==8){
    const int mask1 = (7 << 3);
    const int mask2 = (7 << 0);
    firstDigit = (decimal & mask1);
    secondDigit = (decimal & mask2);
    printf("Octal Representation of Binary Number: %i%i\n", ascii[firstDigit], ascii[secondDigit]);
}
    
}