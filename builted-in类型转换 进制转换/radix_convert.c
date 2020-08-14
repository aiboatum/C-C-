#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

void reverse(char* arr, int i, int j) {
    for (; i < j; ++i, --j) {
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

char* Dec2Hex(int num, char * str) {
    const char map[] = "0123456789ABCDEF";
    unsigned int n = *(unsigned int*)&num;
    int i = 0;
    do {
        str[i++] = map[n & 0xf];
        n >>= 4;
    } while (n);
    // 加上尾置0
    str[i] = '\0';
    reverse(str, 0, i - 1);
    return str;
}

int Hex2Dec(char* str) {
    int ret = 0;
    for (; *str; ++str)ret = ret * 16 + (isdigit(*str) ? *str - '0' : *str - 'A' + 10);
    return ret;
}


char * Dec2Bin(int num, char* str) {
    const char map[] = "0123456789ABCDEF";
    unsigned int n = *(unsigned int *)&num;
    int i = 0;
    do {
        str[i++] = map[n & 0x1];
        n >>= 1;
    } while (n);

    str[i] = '\0';
    reverse(str, 0, i - 1);
    return str;
}

int Bin2Dec(char* str) {
    int ret = 0;
    // for (; *str; ++str)ret = ret * 2 + *str - '0';
    for (; *str; ++str)ret = (ret << 1) | (*str - '0');
    return ret;
}

// 八进制和十进制的代码略过
// 其余的可以查看 itoa 的实现
int main() {
    char str[100];
    printf("Dec2Hex : %s\n",Dec2Hex(-1,str));
    printf("Hex2Dex : %d\n", Hex2Dec("FFFFFFFF"));
    printf("Dec2Bin : %s\n", Dec2Bin(-1, str));
    printf("Bin2Dec : %d\n", Bin2Dec("1111111111111111111111111111111"));
}