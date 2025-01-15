#!/bin/bash

if [[ $1 == "-e" ]]; then
	cc srcs/exec.c srcs/error.c libft/*.c && ./a.out
else
	echo "not set"
fi
