#include "str_replace.h"

char *str_replace(char *str, const char from, const char to) {
    char *strStart = str;

    while (*strStart != '\0') {
        if (*strStart == from) {
            *strStart = to;
        }

        strStart++;
    }

    return str;
}
