#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

int myAtoi(char *str) {
    int ans = 0;
    while (isspace(*str))
        str++;

    bool negtive = false;

    if (*str == '-') {
        ++str;
        negtive = true;
    } else if (*str == '+') {
        ++str;
        negtive = false;
    } else if (!isdigit(*str)) {
        return 0;
    }

    while (*str && isdigit(*str)) {
        int temp = (unsigned)ans * 10 + *str - '0';
        if (temp / 10 != ans)
            return negtive ? INT_MIN : INT_MAX;
        ans = temp;
        str++;
    }
    return (negtive) ? -ans : ans;
}

int main() { printf("%d", myAtoi("  +91283472332 words  ")); }