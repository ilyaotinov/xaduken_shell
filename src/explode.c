#include "explode.h"
#include <stdlib.h>
#include <string.h>

size_t token_cnt(char *str, const char delim) {
    size_t count = 0;
    if (str == NULL) {
        return count;
    }
    count++;
    
    size_t pointer = 0;

    while(*(str + pointer) != '\0') {
        if (*(str + pointer) == delim) {
            count++;
        }
        pointer++;
    }

    return count;
}

char **explode(char *str, const char delimiter)
{
    size_t token_count = token_cnt(str, delimiter);
    char *token = strtok(str, &delimiter);   
    if (token == NULL) {
        return NULL;
    }

    char **tokens = malloc(sizeof(char *) * (token_count + 1));

    if (tokens == NULL) {
        return NULL;
    }

    size_t i = 0;
    tokens[i] = token;
    while (token != NULL) {
        i++;
        token = strtok(NULL, &delimiter);
        tokens[i] = token;
    }

    tokens[token_count] = NULL;

    return tokens;
}