#!/bin/bash

if [[ $1 == "-e" ]]; then
	cc -Werror -Wextra -Wall srcs/exec.c srcs/ft_echo.c srcs/ft_cd.c srcs/error.c libft/*.c && ./a.out
elif [[ $1 == "-n" ]]; then
	norminette srcs/cd_utils.c srcs/cd_utils_2.c srcs/exec.c srcs/exec_utils.c srcs/exec_utils.c srcs/ft_cd.c srcs/ft_env.c srcs/ft_echo.c srcs/ft_export.c srcs/ft_pwd.c srcs/ft_unset.c srcs/ft_cd.c srcs/redirections.c srcs/export_utils.c srcs/export_utils_2.c
elif [[ $1 == "-ve" ]]; then
	cc -Werror -Wextra -Wall srcs/exec.c srcs/ft_echo.c srcs/ft_cd.c srcs/error.c libft/*.c && valgrind ./a.out
else
	echo "not set"
fi
