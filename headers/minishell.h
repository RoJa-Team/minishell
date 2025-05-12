/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 11:13:42 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define INPUT 0
# define OUTPUT 1
# define APPEND 2
# define HEREDOC 2
# define OUT 1
# define IN 1
// # define malloc(...) NULL

typedef struct s_redir
{
	int				type;
	int				operator;
	char			**file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_arg
{
	char			*word;
	struct s_arg	*next;
}				t_arg;

typedef struct s_exec
{
	int				prev_fd;
	char			*pwd;
}				t_exec;

typedef struct s_cmd
{
	int				cmd_status;
	int				pid;
	int				fd[2];
	char			*error_msg;
	char			**arg;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_parse
{
	t_cmd			*cmd_ll;
	t_arg			*arg_ll;
}				t_parse;

typedef struct s_env
{
	int				invis;
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_catch
{
	char			*error_msg;
}				t_catch;

typedef struct s_dummy
{
	t_redir			redir;
	t_parse			parse;
	t_arg			arg;
	t_cmd			cmd;
	t_env			env;
}				t_dummy;

typedef struct s_ms
{
	int				here_sig;
	int				exit_status;
	char			**ms_env;
	t_env			*env_lst;
	t_cmd			**cmd;
	t_exec			*exec;
}				t_ms;

/*********************************************/
/*                                           */
/*                  Parsing                  */
/*                                           */
/*********************************************/

/* parse_verifications.c */
int		verify_quotes(char *input);
int		verify_heredocs(char *input);
int		verify_redirections(char *input);
int		verify_pipes(char *input);
int		verify_input(char *input);

/* parse_input.c */
char	*new_str(char *str, int *i);
void	new_arg(char **str);
void	new_cmd(void);
void	parse_input(char *str);
void	input_check(char *input);

/* parse_expansions.c */
int		final_len(char *str, int len, int quotes);
void	final_str(char *str, char *arg, int i, int quotes);
char	**expand_str(char *str);

/* parse_expansions_split.c */
char	**allocate_split(char *arg);
char	**allocate_strs(char **split_arg, char *arg, int n_str, int quotes);
char	**split_expansion(char *arg, int i, int n_str, int quotes);

/* parse_expansions_quotes.c */
int		final_str_len(char *split_arg);
void	no_quotes_str(char *str_arr, char *split_arg);
char	**remove_quotes(char **split_arg, int n_strs);

/* parse_expansions_utils.c */
char	*convert_exit_status(void);
char	*find_env_value(char *str, int i, int key_len);
char	*expansion_value(char *str, int *i, int flag);

/* parse_redirections.c */
t_redir	*alloc_redir(int type, int operator);
void	add_redir(char *str, int *i, int type, int operator);
void	new_redir(char *str, int *i);

/* parse_redirections_utils.c */
int		heredoc_quote(char *str);
int		heredoc_del_final_len(char *str);
void	heredoc_del_final_str(char *str, char *final_del);
char	*remove_quotes_heredoc(char *str);

/* parse_heredoc.c */
void	receive_content(char *del, int here, int quote);
int		check_existing_heredoc(void);
char	**handle_heredoc(int quote, char *delimiter);

/* parse_heredoc_expansions.c */
int		here_len(char *line);
char	*final_here(char *str, char *arg, int i);
char	*expand_here(char *line);

/* parse_ll_to_array.c */
void	token_to_array(void);
void	cmd_to_array(void);

/* parse_misc.c */
int		within_quotes(char *str);
int		check_metachar(char c);
void	check_quotes(char c, int *quotes);

/*********************************************/
/*                                           */
/*                 Executing                 */
/*                                           */
/*********************************************/

/*exec.c*/
void	exec_cmd(void);
void	handle_input(int *i, int *save_stdin, int *save_stdout);
int		is_builtin(int i);
void	fork_child_process(int *i, int *prev_fd);
void	execute_builtin(int i);

/*exec_utils.c*/
char	*get_value(t_env *env, char *key);
char	*find_path(t_env *env_lst, char *cmd);
char	*get_full_path(char *path_dir, char *cmd);
void	close_pipe(int *fd, int *prev_fd, int i);
void	save_and_restore_std(int *save_stdin, int *save_stdout, int flag);

/*exec_utils_2.c*/
void	close_heredoc(int i);
void	not_found(int i);
void	execute_execve(int i);
void	child_process(int prev_fd, int *fd, int i, int res);
void	check_next_pipe(int i, int *fd);

/*exec_utils_3.c*/
void	execute_builtin_or_execve(int i);
int		is_executable(const char *path);
void	remove_key(t_env *prev, t_env *temp, char *arg);
void	wait_for_childs(void);
void	not_found_case(int i);

/*ft_echo_pwd_env_unset.c*/
void	ft_echo(int i);
void	ft_pwd(void);
void	ft_unset(int i);
int		check_n_flag(char **arg);
void	ft_env(int i);

/*ft_cd.c*/
void	ft_cd(int i);
void	assign_to_ms_env(void);
void	change_directory(char *oldpwd, char *newpwd, int i);
void	assign_visible(t_env *temp2, char *temp3, int *i);

/*ft_cd_utils.c*/
char	*get_pwd(t_env *env);
char	*get_home(t_env *env, t_cmd *cmd);
char	*get_parent_dir(char *ab_path);
char	*get_ab_path(char *ab_path, char *next_dir);
char	*check_pwd(char *oldpwd);

/*ft_cd_utils_2.c*/
void	update_env_lst(t_env *env, char *key, char *new_value);
void	update_ms_env(void);
void	free_args(char **arg);
int		arg_count(char **arg);
void	no_value(char *arg, char **key, char **value);

/*ft_cd_utils_3.c*/
char	*cd_no_file(char *oldpwd, char *newpwd, int i);
char	*cd_cases(char **split_path, char *ab_path, char *temp, int i);

/*ft_export.c*/
void	ft_export(int i);
void	add_new_key(char **arg, int j, int i);
void	print_export_fd(void);
void	execute_export(int fd, char *line);
void	sort_env(char **env);

/*ft_export_utils.c*/
void	get_key_and_value(char *arg, char **key, char **value);
int		is_valid_key(char *key);
void	update_or_add_env_key(t_env **env, char *key, char *value);
void	add_env_key(t_env **env, char *key, char *value);
void	swap_str(char **a, char **b);

/*ft_export_utils_2.c*/
char	**convert_lst_to_arr(t_env *lst);
int		env_lst_size(t_env *env_lst);
int		assign_value_to_array(int *i, t_env *lst, char **arr);
void	free_key_and_value(char *key, char *value);
char	*find_value(t_env *env, char *key);

/*exec_redirections.c*/
int		handle_redirections(t_cmd *cmd);
void	handle_input_r(t_cmd *cmd, t_redir *r, int *res);
void	handle_output_r(t_cmd *cmd, t_redir *r, int *res);
void	execute_heredoc(t_cmd *cmd, t_redir *r, int *res, struct stat st);
void	check_access(t_cmd *cmd, t_redir *r, int *res, struct stat st);

/*exec_redirections_utils.c*/
void	ambiguous_redirect(t_cmd *cmd, int *res);
int		check_redir_input(t_redir *redir);
int		check_redir_output(t_redir *redir);

/*ft_exit.c*/
int		is_numeric(const char *str);
int		is_ll_overflow(const char *str);
void	ft_exit(int i);
void	numeric_message(int i);

/*********************************************/
/*                                           */
/*          Miscellanious functions          */
/*                                           */
/*********************************************/

/* init_ms.c */
void	copy_env(char **env);
t_env	*new_env(int i);
void	create_env_lst(void);
void	init(char **env);

/* static_structs.c */
t_ms	*ms(void);
t_parse	*parse(void);
t_dummy	*dummy(void);
t_catch	*catch(void);

/* signals.c */
void	setup_parse(void);
void	setup_exec(void);
void	setup_heredoc(void);
void	setup_signal(int signum, void (*sig_handler)(int), int flag);

/* signals_utils.c */
void	heredoc_signal(int signal);
void	parse_signal(int signal);
void	exec_signal(int signal);
int		rl_hook(void);

/* list_functions.c */
size_t	get_offset(void *struct_ptr, void *member_ptr);
int		get_list_size(void *node, size_t next_offset);
void	*get_last_node(void *node, size_t next_offset);

/* error.c */
void	free_array(char **split_arg);
void	bad_input(char *message, int error);
void	deallocate(void);

/* cleaner.c */
void	clean_env_lst(void);
void	clean_ms_env(void);
void	clean_redir(void);
void	clean_cmd(void);
void	clean_structs(void);

/* cleaner_ll.c */
void	clean_arg_ll(void);
void	clean_redir_ll(t_cmd *cmd_temp);
void	clean_parse(void);

#endif
