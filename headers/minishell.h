/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/27 20:50:50 by joafern2         ###   ########.fr       */
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

// HOME=/home
// if unset HOME
// cd $HOME (é suposto dar erro aqui porque $HOME está unset, mas ao passar para o executor ela já vai expanded)
// cd ~/home
//
//if export is used, set to 1, if cd is used set to 0 // cd $OLDPWD 
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
	// if expanded 
	//	 cd $OLDPWD -> cd 42
	// else
	//	cd $OLDPWD -> cd NULL

	// OLDPWD = 42
	// export OLDPWD=batata -> modified = 1
	// invis = 0
	// cd $OLDPWD -> cd batata



typedef struct s_redir
{
	int				del;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_arg
{
	char			*str; // '$OLDPWD' $OLDPWD  $OLDPWD 42
	char			*env_key;
}				t_arg;

typedef struct s_cmd
{
	//char	**args; // ls srcs > out
	t_arg	**arg; // ls NULL srcs
	t_redir	*fd_in; // [{file:"a", del:0}, {file:"b", del:0}, {file:"", del:0}]
	// echo 123 < a < b << eof > out >> out2 > out
	t_redir	*fd_out;
}				t_cmd;

typedef struct s_env
{
	int				invis;
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_parse
{
	int				quotes; // 0 1 2
	char			*token;
	struct s_parse	*next;
}				t_parse;

typedef struct s_ms
{	
	char		**ms_env;
	char		*og_home;
	t_env		*env_lst;
	t_parse		*parse;
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
char	*find_path(t_env *env_lst, char *cmd);
int	is_builtin(t_ms *ms, int i);
char	*get_value(t_env *env, char *key);
char	**convert_args_to_char(t_ms *ms, int h);

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
char	*get_oldpwd(t_env *env);
void	free_args(char **arg);

/*********************************************/
/*                                           */
/*          Miscellanious functions          */
/*                                           */
/*********************************************/

/* error.c */
void	deallocate(char *message);

#endif
