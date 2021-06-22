#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *arr, int i, int j) {
    for (; i < j; ++i, --j) {
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

char *Dec2Hex(int num, char *str) {
    const char map[] = "0123456789ABCDEF";
    unsigned int n = *(unsigned int *)&num;
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

int Hex2Dec(char *str) {
    int ret = 0;
    for (; *str; ++str)
        ret = ret * 16 + (isdigit(*str) ? *str - '0' : *str - 'A' + 10);
    return ret;
}

char *Dec2Bin(int num, char *str) {
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

int Bin2Dec(char *str) {
    int ret = 0;
    // for (; *str; ++str)ret = ret * 2 + *str - '0';
    for (; *str; ++str)
        ret = (ret << 1) | (*str - '0');
    return ret;
}

// 八进制和十进制的代码略过
// 其余的可以查看 itoa 的实现
int main() {
    char str[100];
    printf("Dec2Hex : %s\n", Dec2Hex(-1, str));
    printf("Hex2Dex : %d\n", Hex2Dec("FFFFFFFF"));
    printf("Dec2Bin : %s\n", Dec2Bin(-1, str));
    printf("Bin2Dec : %d\n", Bin2Dec("1111111111111111111111111111111"));
    char out[33];
    for (int s = 2; s < 36; s++) {
        radix_convert("a1b2c3", 16, out, s);
        printf("16:a1b2c3 => %2d : %s\n", s, out);
    }
    for (int s = 2; s < 36; s++) {
        radix_convert("10000", 10, out, s);
        printf("10:10000 => %2d : %s\n", s, out);
    }
}

// 36 进制之间的转换
void radix_convert(char *in, int s_in, char *out, int s_out) {

    int v = 0, n;
    for (char *p = in; *p; p++)
        v = v * s_in + (*p - ((*p >= 'a') ? ('a' - 10) : '0'));
    for (n = 31; v && n; v = v / s_out)
        out[n--] = (((v % s_out) < 10) ? '0' : ('a' - 10)) + (v % s_out);
    memmove(out, out + n + 1, 32 - n - 1);
    out[32 - n - 1] = 0;
}

/***
 * 作者：泾渭漳淮
 * 链接：https://www.zhihu.com/question/430885980/answer/1640970548
 * 来源：知乎
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 **/