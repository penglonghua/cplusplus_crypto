#include <stdio.h>
#include "chacha.h"
#include "rand.h"
#include "util.h"

int main(void) {

    size_t length = 50;
    char repeat = '-';
    char *line = repeat_char(length, repeat);

    printf(" %s start %s \n", line, line);

    // rand_case1();
    // chacha_case1();
    // chacha_case2();
    chacha_case3();

    printf(" %s  end  %s \n", line, line);


    free_char(line);
    return 0;
}
