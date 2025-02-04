/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/04 04:22:07 by joafern2         ###   ########.fr       */
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

typedef struct s_redir
{
	int				del;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_arg
{
	char	*str;
	char	*env_key;
}				t_arg;

typedef struct s_cmd
{
	t_arg	**arg;
	t_redir	*fd_in;
	t_redir	*fd_out;
}				t_cmd;

typedef struct s_env
{
	int				invis;
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

// export -> modified = 0 or 1 && invis = 0
// cd -> modified = 0 && invis = invis
// unset -> invis = 1

// OLDPWD = 42
// modified = 0
// unset OLDPWD -> invis = 0
// cd $OLDPWD -> cd 42

// OLDPWD = 42
// export OLDPWD=batata -> modified = 1
// unset OLDPWD -> invis = 1
// cd $OLDPWD -> cd NULL

// OLDPWD = 42
// modified = 0
// unset OLDPWD -> invis = 1
// cd $OLDPWD -> cd 42

// OLDPWD = 42
// export OLDPWD=batata -> modified = 1
// invis = 0
// cd $OLDPWD -> cd batata

typedef struct s_parse
{
	int				quotes; // 0 1 2
	char			*token;
	struct s_parse	*next;
}				t_parse;

typedef struct s_ms
{	
	char	*og_home;
	char	**ms_env;
	t_env	*env_lst;
	t_parse	*parse;
	t_cmd	**cmd;
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
char	*find_path(t_env *env_lst, char *cmd);
int	is_builtin(t_ms *ms, int i);
char	*get_value(t_env *env, char *key);
char	**convert_args_to_char(t_ms *ms, int h);
int	node_count(t_arg **arg);

/*ft_echo.c*/
int	ft_echo(t_ms *ms, int i);

/*ft_cd.c*/
int	ft_cd(t_ms *ms, int i);
char	*get_pwd(t_env *env);
char	*get_home(t_env *env);
void	update_env_lst(t_env *env, char *key, char *new_value);
void	update_ms_env(t_ms *ms);
char	*get_home_til(t_ms *ms);
char	*print_oldpwd(t_env *env);
char	*get_ab_path(char *ab_path, char *next_dir);
char	*get_oldpwd(t_env *env);
void	free_args(char **arg);
int	arg_count(char **arg);

/*ft_pwd.c*/
int     ft_pwd(t_ms *ms);

/*********************************************/
/*                                           */
/*          Miscellanious functions          */
/*                                           */
/*********************************************/

/* error.c */
void	free_array(char	**array);
void	clean_parse(t_ms *ms);
void	clean_cmd(t_ms *ms);
void	deallocate(char *message);

#endif
