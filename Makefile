# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 19:02:07 by rafasant          #+#    #+#              #
#    Updated: 2025/04/02 21:19:17 by joafern2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RL		= -lreadline -lhistory
NAME 	= minishell
LIBFT 	= libft/libft.a
SRCS_DIR= srcs/
OBJS_DIR= objs/
SRCS 	= $(addprefix ${SRCS_DIR}, minishell.c init_ms.c error.c \
			list_functions.c print_functions.c parse_input.c parse_heredoc.c \
			parse_ll_to_array.c parse_misc.c parse_redirections.c \
			parse_expansions.c parse_expansions_utils.c \
			export_utils_2.c exec_utils.c cd_utils.c \
			cd_utils_2.c signals.c ft_exit.c \
			ft_echo.c ft_cd.c ft_pwd.c ft_export.c ft_unset.c \
			ft_env.c exec.c export_utils.c redirections.c)
OBJS	= ${SRCS:${SRCS_DIR}%.c=${OBJS_DIR}%.o}
RM	= /bin/rm -f

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@${CC} ${CFLAGS} -c $< -o $@

all: ${LIBFT} ${NAME}
${LIBFT} :
	@echo "Compiling libft..."
	@make -C libft --silent
	@echo "Libft compiled!"
${NAME} : ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${RL} -o ${NAME}
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
