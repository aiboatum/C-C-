/*--------------------------------------------------------
 *                      C语言实现单词统计
 *                      created date: 2018年研究生复试前夕
 *                      updated: 2020/7/25
 *---------------------------------------------------------*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h> //利用fscanf和fprintf函数完成此功能
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)
typedef struct _Words {
    char str[30];
    int count;
    int tag; //标志该结构体是否已被使用
} Words;
int f_scanf(FILE *, char *);
int f_scanf(FILE *p, char *ch) {
    int c;
    while (!isalpha(c = getc(p)) && c != EOF)
        continue; //排除开头非字母
    ch[0] = c;
    int i = 1;
    while (isalpha(c = getc(p)) && c != EOF) {
        ch[i++] = c;
    }
    ch[i] = '\0';
    if (c == EOF)
        return 0;
    else
        return 1;
}

int cmp(const void *a, const void *b) {
    return ((Words *)b)->count - ((Words *)a)->count;
}

#define MAX_NUM_OF_WORDS 1000

int main(void) {
    Words *words_cnt = (Words *)calloc(MAX_NUM_OF_WORDS, sizeof(*words_cnt));
    assert(words_cnt);
    // Words words_cnt[100] = { {.count = 0,.tag = 0} };
    FILE *p;
    p = fopen("C:/Users/15931/Documents/GitHub/C-CPP/test.txt", "r");
    assert(p);

    char temp[30];
    int total_cnt = 0;
    while (f_scanf(p, temp) == 1) {
        for (int i = 0; i < MAX_NUM_OF_WORDS; ++i) {
            if (words_cnt[i].tag == 0) {
                strcpy(words_cnt[i].str, temp);
                words_cnt[i].tag = 1;
                words_cnt[i].count++;

                ++total_cnt;
                break;
            } else if (strcmp(temp, words_cnt[i].str) == 0) {
                words_cnt[i].count++;
                break;
            }
        }
    } //从中file中读取一个单词放入s结构体的char s[30]中
    fclose(p);
    qsort(words_cnt, MAX_NUM_OF_WORDS, sizeof(words_cnt[0]), cmp);
    printf("\n---------------------words count--------------------------\n");
    printf("total number of words : %d\n", total_cnt);
    for (int i = 0; words_cnt[i].tag; i++)
        printf("%s : %d\n", words_cnt[i].str, words_cnt[i].count);
    free(words_cnt);
    printf("-----------------------end count--------------------------\n");
}