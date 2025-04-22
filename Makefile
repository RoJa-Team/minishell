# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 19:02:07 by rafasant          #+#    #+#              #
#    Updated: 2025/04/22 18:38:26 by joafern2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RL		= -lreadline -lhistory
NAME 	= minishell
LIBFT 	= libft/libft.a
SRCS_DIR= srcs/
OBJS_DIR= objs/
SRCS 	= $(addprefix ${SRCS_DIR}, minishell.c \
			init_ms.c static_structs.c list_functions.c print_functions.c \
			error.c cleaner.c \
			parse_verifications.c parse_input.c \
			parse_expansions.c parse_expansions_utils.c \
			parse_redirections.c parse_redirections_utils.c \
			parse_heredoc.c parse_heredoc_expansions.c \
			parse_ll_to_array.c parse_misc.c \
			export_utils_2.c exec_utils.c cd_utils.c \
			cd_utils_2.c signals.c ft_exit.c exec_utils_2.c \
			ft_echo.c ft_cd.c ft_pwd.c ft_export.c ft_unset.c \
			ft_env.c exec.c export_utils.c redirections.c signals_2.c)
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

v :	$(NAME)
	valgrind --suppressions=read.supp --show-leak-kinds=all --leak-check=full ./minishell

vf : $(NAME)
	valgrind --suppressions=read.supp --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes ./minishell

vp : $(NAME)
	valgrind --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes ./minishell

re: fclean all

.PHONY: clean, fclean, all, re
