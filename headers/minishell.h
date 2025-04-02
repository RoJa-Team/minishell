/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/02 21:21:30 by joafern2         ###   ########.fr       */
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
//TODO remove this
# define debug(info, x) _Generic((x), int: print_int, char *: print_string)(info, x)
// USAGE: debug(mensagem, variavel);
# define APPEND 2
# define HEREDOC 2
# define OUT 1
# define IN 1
// cat << 1 | cat << 2 | cat << 3 | cat << 4 | cat << 5 | cat << 6 | cat << 7 | cat << 8 | cat << 9 | cat << 10 | cat << 11 | cat << 12 | cat << 13 | cat << 14 | cat << 15 | cat << 16 | cat << 17 | cat << 18 | cat << 19 | cat << 20 
// cat << here > out | lsl | cat < out | wc
// cat << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 
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

typedef struct s_exec
{
	int	prev_fd;
}				t_exec;

typedef struct s_cmd
{
	char			**arg;
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

typedef struct s_dummy
{
	t_heredoc	heredoc;
	t_redir		redir;
	t_parse		parse;
	t_cmd		cmd;
	t_env		env;
}				t_dummy;

typedef struct s_ms
{
	char	**ms_env;
	t_env	*env_lst;
	t_cmd	**cmd;
	t_exec	*exec;
	t_dummy	dummy;
	int	exit_status;
}				t_ms;

/*********************************************/
/*                                           */
/*                  Parsing                  */
/*                                           */
/*********************************************/

/* init_ms.c */
void	init_ms(char **env);
void	copy_env(char **env);

/* parse_input.c */
void	new_cmd(t_cmd **cmd_ll);
char	*new_str(char *str, int *i);
void	new_arg(t_parse **arg_ll, char *str);
void	parse_input(char *str);

/* parse_expansions.c */
int		exp_len(char *str);
char	*expand_str(char *str);
char	*expansion_value(char *str, int *i);
int		expansion_len(char *str, int *i);
char	*final_str(char *str, char *arg, int i);

/* parse_expansions_utils.c */
char	*find_env_value(char *str, int i, int key_len);

/* parse_redirections.c */
int		file_len(char *str, int i);
char	*get_file(char *str, int *i);
void	new_output(t_cmd *cmd_ll, char *file, int type);
void	new_input(t_cmd *cmd_ll, char *file, int type);
void	new_redir(t_cmd *cmd_ll, char *str, int *i);

/* parse_heredoc.c */
int		handle_heredoc(char *delimiter);

/* parse_misc.c */
t_ms	*ms(void);
int		within_quotes(char *str);
int		check_metachar(char c);
void	check_quotes(char c, int *quotes);
void	verify_input(char *input);
void	verify_quotes(char *input);
void	verify_heredocs(char *input);


/* parse_ll_to_array.c */
void	token_to_array(t_cmd *cmd_ll, t_parse *arg_ll);
void	cmd_to_array(t_cmd *cmd_ll);

/*********************************************/
/*                                           */
/*                 Executing                 */
/*                                           */
/*********************************************/

/*exec.c*/
void	exec_cmd(void);
void	handle_input(int *i, int *save_stdin, int *save_stdout);
int		is_builtin(int i);
void	child_process(int prev_fd, int *fd, int i);
void	execute_execve(int i);
void	execute_builtin(int i);

/*exec_utils.c*/
char	*get_value(t_env *env, char *key);
char	*find_path(t_env *env_lst, char *cmd);
void	save_and_restore_std(int *save_stdin, int *save_stdout, int flag);
char	*get_full_path(char *path_dir, char *cmd);
void	close_pipe(int *fd, int *prev_fd, int i);

/*ft_echo.c*/
void	ft_echo(int i);

/*ft_cd.c*/
void	ft_cd(int i);
char	*print_oldpwd(t_env *env);
void	assign_to_ms_env(void);
char	*check_visibility(t_env *temp);
void	change_directory(char *oldpwd, char *newpwd, int i);

/*cd_utils.c*/
char	*get_pwd(t_env *env);
char	*get_home(t_env *env);
char	*get_parent_dir(char *temp, char *ab_path);
char	*get_ab_path(char *ab_path, char *next_dir);

/*cd_utils_2.c*/
void	update_env_lst(t_env *env, char *key, char *new_value);
void	update_ms_env(void);
void	free_args(char **arg);
int		arg_count(char **arg);

/*ft_pwd.c*/
void	ft_pwd(void);

/*ft_export.c*/
void	ft_export(int i);
void	add_new_key(char **arg, int j);
void	print_export_fd(void);
void	execute_export(int fd, char *line);
void	sort_env(char **env);

/*export_utils.c*/
void	get_key_and_value(char *arg, char **key, char **value);
int		is_valid_key(char *key);
void	update_or_add_env_key(t_env **env, char *key, char *value);
void	add_env_key(t_env **env, char *key, char *value);
void	swap_str(char **a, char **b);

/*export_utils_2.c*/
char	**convert_lst_to_arr(t_env *lst);
int		env_lst_size(t_env *env_lst);
int		assign_value_to_array(int *i, t_env *lst, char **arr);
void	free_key_and_value(char *key, char *value);
char	*find_value(t_env *env, char *key);

/*ft_unset.c*/
void	ft_unset(int i);
void	remove_key(t_env *prev, t_env *temp, char *arg);

/*ft_env.c*/
void	ft_env(int i);

/*redirections.c*/
int	handle_redirections(t_cmd *cmd);
void	handle_input_r(t_redir *r, int *res);
void	handle_output_r(t_redir *r, int *res);
void	execute_heredoc(t_redir *r, int *res);
void	check_access(t_redir *r, int *res);

/*signal.c*/
void	signal_handler(int signum);
void	setup_signals(void);

/*ft_exit.c*/
int	is_numeric(const char *str);
int	is_ll_overflow(const char *str);
void	cleanup(void);
void	ft_exit(int i);


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

void	print_ms_env(void);
void	print_env_lst(void);
void	print_cmd(void);
void	print_int(char *info, int data);
void	print_string(char *info, char *data);

/*********************************************/
/*                                           */
/*          Miscellanious functions          */
/*                                           */
/*********************************************/

/* error.c */
void	free_array(char	**array);
void	clean_parse(void);
void	clean_cmd(void);
void	deallocate(char *message);

#endif
