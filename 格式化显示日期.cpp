#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    int y = atoi(argv[1]);
    printf("%32d\n", y);
    int md[12] = {31, (y % ((y % 100) ? 4 : 400)) ? 28 : 29,
                  31, 30,
                  31, 30,
                  31, 31,
                  30, 31,
                  30, 31};

    struct tm t;
    memset(&t, 0, sizeof(struct tm));
    t.tm_year = y - 1900;
    int w1 = (mktime(&t) / 3600 / 24 + 6) % 7, w2 = (w1 + 31) % 7;

    for (int m = 0; m < 12; m += 2) {
        int d1 = 1 - w1, d2 = 1 - w2;
        printf("\n%16d%30d\n", m + 1, m + 2);
        printf(" Sun Mon Tue Wed Thu Fri Sat   Sun Mon Tue Wed Thu Fri Sat\n");
        while ((d1 <= md[m]) || (d2 <= md[m + 1])) {
            for (int i = 0; i < 7; i++, d1++)
                printf(((d1 > 0) && (d1 <= md[m])) ? "%4d" : "    ", d1);
            printf("  ");
            for (int i = 0; i < 7; i++, d2++)
                printf(((d2 > 0) && (d2 <= md[m + 1])) ? "%4d" : "    ", d2);
            printf("\n");
        }

        w1 = (w2 + md[m + 1]) % 7;
        w2 = (w1 + md[m + 2]) % 7;
    }
}