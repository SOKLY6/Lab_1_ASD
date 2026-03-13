#include <stdio.h>

int input_value(int *value) {
    char c;
    if (scanf("%d%c", value, &c) == 2 && c == '\n') {
        return 0;
    } else {
        while (getchar() != '\n');
        return 1;
    }
}