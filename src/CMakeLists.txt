project(simple_shell)

cmake_minimum_required(VERSION 3.10)

include_directories(headers)

set(READLINE_SOURCE, headers/readline.h readline.c)
set(EXPLODE_SOURCE headers/explode.h explode.c)

set(SHELL_SOURCE ${READLINE_SOURCE} ${EXPLODE_SOURCE})

add_executable(xaduken_shell main.c ${SHELL_SOURCE})