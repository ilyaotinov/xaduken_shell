#include <stdlib.h>
#include <stdio.h>
#include <explode.h>
#include <stdbool.h>
#include "readline.h"
#include "str_replace.h"
#include "getenv.h"
#include <string.h>
#include "explode.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void type_prompt()
{
    printf("xdauken $ ");
}

bool file_exists(char *filename)
{
    FILE *file = fopen(filename, "r");
    bool result = file != NULL;
    if (file != NULL)
    {
        fclose(file);
    }

    return result;
}

char *get_command(char *user_input)
{
    if (user_input == NULL)
    {
        return NULL;
    }
    char *user_input_buffer = malloc(sizeof(char) * (strlen(user_input) + 1));
    strcpy(user_input_buffer, user_input);
    char *command_name = strtok(user_input_buffer, " ");

    char **env_arr = get_env_arr();

    char *command = NULL;
    for (int i = 0; env_arr[i] != NULL; i++)
    {
        if (command != NULL)
        {
            free(command);
        }
        size_t command_size = sizeof(char) * (strlen(env_arr[i]) + strlen(command_name) + 2);
        command = malloc(command_size);
        command = strcpy(command, env_arr[i]);
        command[strlen(env_arr[i])] = '/';
        command = strcat(command, command_name);
        command[command_size - 1] = '\0';

        if (file_exists(command))
        {
            free(env_arr);
            free(command_name);
            return command;
        }
    }
    free(env_arr);
    free(command);
    return NULL;
}

char **get_argv(char *user_input)
{
    return explode(user_input, ' ');
}

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;

    while (true)
    {
        type_prompt();
        char *user_input = readline(stdin);
        char **user_argv = get_argv(user_input);
        char cd[] = "cd";
        char exit[] = "exit";

        if (fork() != 0)
        {
            if (strcmp(user_input, exit) == 0)
            {
                break;
            }
            if (strcmp(user_input, cd) == 0)
            {
                if (user_argv[1] != NULL)
                {
                    chdir(user_argv[1]);
                } else {
                    printf("Error: No argument given\n");
                }
            }
            wait(NULL);
        }
        else
        {
            if (user_input == NULL)
            {
                printf("\n");
                break;
            }

            char *command = get_command(user_input);

            if (strcmp(user_input, exit) == 0)
            {
                printf("Xaduken say goodby\n");
                break;
            }
            if (strcmp(user_input, cd) == 0)
            {
                break;
            }
            if (command == NULL)
            {
                status = EXIT_FAILURE;
                printf("command: %s not found\n", user_input);
                free(user_input);
                break;
            }

            execv(command, user_argv);
            free(user_input);
            break;
        }
    }

    return status;
}
