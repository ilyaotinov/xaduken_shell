#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline(FILE *in)
{
    size_t strSize = sizeof(char) + 1;
    size_t strLen = 0;
    char *userLine = malloc(strSize);
    char *currentPosition = userLine;
    int ch;

    while ((ch = fgetc(in)) != '\n')
    {
        if ((sizeof(char) * strLen) == (strSize - 1))
        {
            strSize *= 2;
            if ((userLine = realloc(userLine, strSize)) == NULL)
            {
                free(userLine);
                return NULL;
            }
            currentPosition = userLine + strLen;
        }
        *(currentPosition) = ch;
        strLen++;
        currentPosition++;
    }
    *(++currentPosition) = '\0';

    return userLine;
}
