project(simple_shell)

cmake_minimum_required(VERSION 3.10)

include_directories(headers)

set(READLINE_SOURCE headers/readline.h readline.c)
set(EXPLODE_SOURCE headers/explode.h explode.c)
set(STR_REPLACE_SOURCE headers/str_replace.h str_replace.c)
set(GET_ENV_SOURCE headers/getenv.h getenv.c)

set(SHELL_SOURCE ${READLINE_SOURCE} ${EXPLODE_SOURCE} ${STR_REPLACE_SOURCE} ${GET_ENV_SOURCE})

add_executable(xaduken_shell main.c ${SHELL_SOURCE})