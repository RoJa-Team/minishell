/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/11 20:59:27 by rafasant         ###   ########.fr       */
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

# define APPEND 2
# define HEREDOC 2
# define OUT 1
# define IN 1
// cat << 1 | cat << 2 | cat << 3 | cat << 4 | cat << 5 | cat << 6 | cat << 7 | cat << 8 | cat << 9 | cat << 10 | cat << 11 | cat << 12 | cat << 13 | cat << 14 | cat << 15 | cat << 16 | cat << 17 | cat << 18 | cat << 19 | cat << 20 
// cat << here > out | lsl | cat < out | wc
typedef struct s_heredoc
{
	char				*str;
	struct s_heredoc	*next;
}				t_heredoc;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_parse
{
	char			*token;
	struct s_parse	*next;
}				t_parse;

typedef struct s_cmd
{
	char			**arg;
	t_parse			*token;
	t_redir			*fd_in;
	t_redir			*fd_out;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	int				invis;
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_ms
{	
	char	**ms_env;
	t_env	*env_lst;
	t_cmd	*cmds;
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

/* tokens.c */
void	insert_new_token(t_ms *ms, t_parse *new_token);
t_parse	*new_token(char *str, int len);
void	parse_tokens(t_ms *ms, char *str);
char	*expand_token(t_ms *ms, t_parse *token);


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
int	arg_count(char **arg);

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
int     ft_pwd();

/*ft_export.c*/
int	ft_export(t_ms *ms, int i);
void	get_key_and_value(char *arg, char **key, char **value);
int	is_valid_key(char *key);
void	free_key_and_value(char *key, char *value);
void	update_or_add_env_key(t_env **env, char *key, char *value);
void	print_export_fd(t_ms *ms);

/*ft_unset.c*/
int	ft_unset(t_ms *ms, int i);

/*********************************************/
/*                                           */
/*             List functions                */
/*                                           */
/*********************************************/

size_t	get_offset(void *struct_ptr, void *member_ptr);
int		get_list_size(void *node, size_t next_offset);
void	*get_last_node(void *node, size_t next_offset);
void	free_list(void *node, size_t next_offset);


/*********************************************/
/*                                           */
/*             Printing functions            */
/*                                           */
/*********************************************/

void	print_ms_env(t_ms *ms);
void	print_env_lst(t_ms *ms);
void	print_cmd(t_ms *ms);

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
