/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/17 18:20:10 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	//char			**cmd;
	char			**arg;
	char			*fd_in;
	int				heredoc;
	char			*fd_out;
	int				append;
}				t_cmd;

typedef struct s_ms
{
	char		**my_env;
	t_cmd		**cmd;
}				t_ms;

/*********************************************/
/*                                           */
/*                  Parsing                  */
/*                                           */
/*********************************************/

/* init_ms.c */
t_ms	*init_ms(char **env);
void	copy_env(t_ms *ms, char **env);

/* parse_input.c */
int		pipe_counter(char *str);
void	parse_input(t_ms *ms, char *str);
void	quote_validator(char *str);

/*********************************************/
/*                                           */
/*                 Executing                 */
/*                                           */
/*********************************************/

/*exec.c*/
void	exec_cmd(t_ms *ms);
char	*find_path(char *cmd);
int	is_builtin(t_ms *ms, int i);

/*built-ins*/
int	ft_echo(t_cmd *cmd);

/*********************************************/
/*                                           */
/*          Miscellanious functions          */
/*                                           */
/*********************************************/

/* error.c */
void	deallocate(char *message);

#endif
