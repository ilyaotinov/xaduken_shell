#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "explode.h"

#define PATH_NAME "PATH"
#define BUFFER_SIZE 80UL

char *get_path(void) {
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    char *envPtr = getenv(PATH_NAME);
    unsigned long buffer_size = BUFFER_SIZE;

    if (envPtr == NULL) {
        printf("%s is not set\n", PATH_NAME);
        return NULL;
    }

    if (strlen(envPtr) > buffer_size) {
        if (realloc(buffer, strlen(envPtr + 1)) == NULL) {
            free(buffer);
            buffer = NULL;
            printf("%s\n", "failed to allocate memory");
            return NULL;
        }
    }

    strcpy(buffer, envPtr);
    return buffer;
}

char **get_env_arr() {
    char *path = get_path();
    char **paths = explode(path, ':');
    return paths;
}
