#!/bin/bash

if [[ $1 == "-e" ]]; then
	cc -Werror -Wextra -Wall srcs/exec.c srcs/ft_echo.c srcs/ft_cd.c srcs/error.c libft/*.c && ./a.out
elif [[ $1 == "-ve" ]]; then
	cc -Werror -Wextra -Wall srcs/exec.c srcs/ft_echo.c srcs/ft_cd.c srcs/error.c libft/*.c && valgrind ./a.out
else
	echo "not set"
fi
