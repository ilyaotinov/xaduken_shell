#include <stdlib.h>
#include <stdio.h>
#include <explode.h>
#include <stdbool.h>
#include "readline.h"
#include "str_replace.h"
#include "getenv.h"
#include <string.h>

void type_prompt() {
    printf("xdauken $ ");
}

char *remove_space(char *str) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
    return str;
}

bool file_exists(char *filename) {
    FILE *file = fopen(filename, "r");
    bool result = file!= NULL;
    if (file != NULL) {
        fclose(file);
    }

   return result;
}

char *get_command() {
    char *user_input = remove_space(readline(stdin));
    if (user_input == NULL) {
        return NULL;
    }

    char **env_arr = get_env_arr();

    char *command = NULL;
    for (int i = 0; env_arr[i] != NULL; i++) {
        if (command != NULL) {
            free(command);
        }
        size_t command_size = sizeof(char) * (strlen(env_arr[i]) + strlen(user_input) + 2);
        command = malloc(command_size);
        command = strcpy(command, env_arr[i]);
        command[strlen(env_arr[i])] = '/';
        command = strcat(command, user_input);
        command[command_size - 1] = '\0';
        if (file_exists(command)) {
            free(env_arr);
            free(user_input);
            return command;
        }
    }
    free(user_input);
    free(env_arr);
    free(command);
    return NULL;
}

int main(int argc, char *argv[]) {
    int status = EXIT_SUCCESS;
    while (true) {
        type_prompt();
        char *command = get_command();
        if (command == NULL) {
            status = EXIT_FAILURE;
            printf("command not found\n");
            break;
        }
        printf("command: %s\n", command);
        break;
    }

    return status;
}
