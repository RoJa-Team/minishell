# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 19:02:07 by rafasant          #+#    #+#              #
#    Updated: 2025/05/12 10:29:01 by rafasant         ###   ########.fr        #
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
			init_ms.c static_structs.c list_functions.c \
			error.c cleaner.c cleaner_ll.c\
			parse_verifications.c parse_input.c \
			parse_expansions.c parse_expansions_utils.c \
			parse_expansions_split.c parse_expansions_quotes.c\
			parse_redirections.c parse_redirections_utils.c \
			parse_heredoc.c parse_heredoc_expansions.c \
			parse_ll_to_array.c parse_misc.c exec.c \
			ft_export_utils_2.c exec_utils.c ft_cd_utils.c \
			exec_utils_2.c ft_cd_utils_2.c signals.c \
			ft_exit.c ft_echo_pwd_env_unset.c ft_cd.c ft_export.c \
			ft_export_utils.c exec_redirections.c ft_cd_utils_3.c \
			signals_utils.c exec_utils_3.c exec_redirections_utils.c)
OBJS	= ${SRCS:${SRCS_DIR}%.c=${OBJS_DIR}%.o}
RM	= /bin/rm -f

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p objs
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
	@rm -rf objs
	@make clean -C libft --silent
	@echo "Cleaned object files!"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C libft --silent
	@echo "Cleaned executables!"

v :	$(NAME)
	valgrind --suppressions=read.supp --show-leak-kinds=all --leak-check=full ./minishell

vf : $(NAME)
	valgrind --suppressions=/home/rafasant/sgoinfre/42Cursus2024/minishell/read.supp --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes ./minishell

vp : $(NAME)
	valgrind --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes ./minishell

re: fclean all

.PHONY: clean, fclean, all, re
