# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 19:02:07 by rafasant          #+#    #+#              #
#    Updated: 2025/01/09 19:45:34 by rafasant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g -lreadline -lhistory
NAME 	= minishell
LIBFT 	= libft/libft.a
SRCS 	= srcs/minishell.c
OBJS	= ${SRCS:.c=.o}
RM		= /bin/rm -f

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

all: ${LIBFT} ${NAME}
${LIBFT} :
	@echo "Compiling libft..."
	@make -C libft --silent
	@echo "Libft compiled!"
${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
	@echo "Compiled $(NAME)."

clean: 
	@${RM} ${OBJS}
	@make clean -C libft --silent
	@echo "Cleaned object files!"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C libft --silent
	@echo "Cleaned executables!"

re: fclean all

.PHONY: clean, fclean, all, re
