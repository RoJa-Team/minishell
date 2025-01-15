#!/bin/bash

if [[ $1 == "-e" ]]; then
	cc -Werror -Wextra -Wall srcs/exec.c srcs/error.c libft/*.c && ./a.out
else
	echo "not set"
fi
