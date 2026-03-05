#include <stdio.h>

int input_value(int *value) {
    char c;
    if (scanf("%d%c", value, &c) != 2 || c != '\n') {
        return 1;
    }
    return 0;
}