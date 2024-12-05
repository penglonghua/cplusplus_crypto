#include "util.h"
#include <stdlib.h>
#include <string.h>


char *repeat_char(size_t count, char c) {

    // 动态分配内存，+1 是为了添加字符串结束符 '\0'
    char *line = (char *) malloc(count + 1);
    if (line == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // 使用 memset 填充字符
    memset(line, c, count);

    // 确保字符串以 '\0' 结尾
    line[count] = '\0';

    return line;
}

void free_char(char *str) {

    if (str) {
        free(str);
    }

}