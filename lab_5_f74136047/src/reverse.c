#include <string.h>
#include "../include/reverse.h"

char *reverse(char *dest, const char *src) {
    size_t len = strlen(src);
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[len - i - 1];
    }
    dest[len] = '\0';
    return dest;
}

