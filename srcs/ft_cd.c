/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:37:16 by joafern2          #+#    #+#             */
/*   Updated: 2025/02/20 00:59:24 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_pwd(t_env *env)
{
	char	*pwd;

	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			pwd = ft_strdup(env->value);
			if (!pwd)
				deallocate("Memory allocation failed for ft_getcwd\n");
			return (pwd);
		}
		env = env->next;
	}
	return (NULL);
}

char	*get_home(t_env *env)
{
	t_env	*temp;
	char	*home;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "HOME", 5) == 0)
		{
			if (temp->invis == 0)
			{
				home = ft_strdup(temp->value);
				if (!home)
					return (NULL);
				else
					return(home); // check for allocation fail
			}
			else
			{
				ft_printf("cd: HOME not set\n");
				return (NULL);
			}
		
		}
		temp = temp->next;	
	}
	ft_printf("cd: HOME not set\n");
	return (NULL);
}

void	update_env_lst(t_env *env, char *key, char *new_value)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(temp->value);	
			temp->value = ft_strdup(new_value);
			//printf("%s=%s\n", temp->key, temp->value);
			return ;
		}
		temp = temp->next;
	}
}

void	update_ms_env(t_ms *ms)
{
	int	count;
	int	i;
	char	*temp3;
	t_env	*temp1;
	t_env	*temp2;

	count = 0;
	i = 0;
	temp1 = ms->env_lst;
	temp2 = ms->env_lst;
	free_args(ms->ms_env);
	while (temp1 != NULL)
	{
		count++;
		temp1 = temp1->next;
	}
	ms->ms_env = malloc(sizeof(char *) * (count + 1));
	while (temp2 != NULL)
	{
		if (!temp2->invis)
		{
			if (temp2->value)
			{
				temp3 = ft_strjoin(temp2->key, "=");
				ms->ms_env[i] = ft_strjoin(temp3, temp2->value);
				free(temp3);
			}
			else
				ms->ms_env[i] = ft_strdup(temp2->key);
			i++;
		}
		temp2 = temp2->next;
	}
	ms->ms_env[i] = NULL;

}
/*
char	*get_home_til(t_ms *ms)
{
	t_env	*temp;

	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "HOME", 5) == 0)
		{
			if (temp->invis == 0)
				return(ft_strdup(temp->value)); // check for allocation fail
			else
				return(ft_strdup(ms->og_home));
		}
		temp = temp->next;
	}
	return (ft_strdup(ms->og_home));
}
*/
char	*print_oldpwd(t_env *env)
{
	t_env	*temp;
	int	fd;

	fd = 1;
	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 7) == 0)
		{
			if (temp->invis == 0)
			{
				ft_putstr_fd(temp->value, fd);
				ft_putchar_fd('\n', fd);
				return(ft_strdup(temp->value)); // check for allocation fail
			}
			else
			{
				ft_printf("cd: OLDPWD not set\n");
				return (NULL);
			}
		}
		temp = temp->next;
	}
	ft_printf("cd: OLDPWD not set\n");
	return (NULL);
}

void	ft_cd(t_ms *ms, int i)
{
	t_env	*temp;
	char	*oldpwd;
	char	*newpwd;
	char	**arg;
	int	count;

	arg = convert_args_to_char(ms, i);
	count = arg_count(arg);
	if (!arg)
		return ;
	if (count > 2)
	{
		ft_printf("cd: too many arguments\n");
		free(arg);
		return ;
	}
	temp = ms->env_lst;
	newpwd = NULL;
	oldpwd = get_value(temp, "PWD");
	// handle !arg[1] wich should take to the home path if visible
	// handle ~ that takes to home if visible, else takes to original home
	// handle OLDPWD: it doesn't take visibility into account and check modified flag
	// handle - same as OLDPWD but prints path to FD and has custom "not set" messag and takes invisibility into account
	if (count < 2)
		newpwd = get_home(temp);
	/*
	else if (ft_strncmp(arg[1], "~", 2) == 0)
		newpwd = get_home_til(ms);
	else if (ft_strncmp(arg[1], "-", 2) == 0)
		newpwd = print_oldpwd(temp);
	*/
	else
		newpwd = get_ab_path(oldpwd, arg[1]);
	//printf("Before cd: oldpwd=%s\n", oldpwd ? oldpwd : "NULL");
	if (newpwd && chdir(newpwd) != 0)
		ft_printf("cd: %s: No such file or directory\n", ms->cmd[i]->arg[1]);
	else if (newpwd)
	{
		update_env_lst(temp, "OLDPWD", oldpwd);
		update_env_lst(temp, "PWD", newpwd);
		update_ms_env(ms);
	}
	//printf("After cd: newpwd=%s\n", get_value(ms->env_lst, "OLDPWD"));
	if (oldpwd)
		free(oldpwd);
	if (newpwd)
		free(newpwd);
	free_args(arg);
}


// TBC
char	*get_ab_path(char *ab_path, char *next_dir)
{
	char	*new_ab_path;
	char	*temp;
	int	i;

	i = 0;
	if (!next_dir || !ab_path)
		return (NULL);
	if (next_dir[0] == '/')
		return (ft_strdup(next_dir));
	if (next_dir[ft_strlen(next_dir) - 1] == '/')
		next_dir[ft_strlen(next_dir) - 1] = '\0';
	if (ft_strncmp(next_dir, "..", 3) == 0)
	{
		temp = ft_strdup(ab_path);
		i = ft_strlen(temp);
		while (i > 0 && temp[i] != '/')
			i--;
		temp[i] = '\0';
		return (temp);
	}
	if (ft_strncmp(next_dir, ".", 2) == 0)
		return (ft_strdup(ab_path));
	if (ab_path[ft_strlen(ab_path) - 1] != '/')
		temp = ft_strjoin(ab_path, "/");
	new_ab_path = ft_strjoin(temp, next_dir);
	free(temp);
	return (new_ab_path);
}

void	free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	arg_count(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}
