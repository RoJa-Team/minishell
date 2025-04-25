/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:55:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/09 20:22:05 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_parent_dir(char *temp, char *ab_path)
{
	int		i;

	temp = ft_strdup(ab_path);
	i = ft_strlen(temp);
	while (i > 0 && temp[i] != '/')
		i--;
	temp[i] = '\0';
	return (temp);
}

char	*get_ab_path(char *ab_path, char *next_dir)
{
	char	*new_ab_path;
	char	*temp;

	temp = NULL;
	new_ab_path = NULL;
	if (!next_dir || !ab_path)
		return (NULL);
	if (next_dir[ft_strlen(next_dir) - 1] == '/')
		next_dir[ft_strlen(next_dir) - 1] = '\0';
	if (next_dir[0] == '/')
		new_ab_path = ft_strdup(next_dir);
	else if (ft_strncmp(next_dir, "..", 3) == 0)
		new_ab_path = get_parent_dir(temp, ab_path);
	else if (ft_strncmp(next_dir, ".", 2) == 0)
		new_ab_path = ft_strdup(ab_path);
	else if (ab_path[ft_strlen(ab_path) - 1] != '/')
	{
		temp = ft_strjoin(ab_path, "/");
		new_ab_path = ft_strjoin(temp, next_dir);
		free(temp);
	}
	if (!new_ab_path)
		return (catch()->error_msg = "memory allocation fail\n", NULL);
	return (new_ab_path);
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
					return (home);
			}
			else
				break ;
		}
		temp = temp->next;
	}
	ft_printf("cd: HOME not set\n");
	ms()->exit_status = 1;
	return (NULL);
}

char	*get_pwd(t_env *env)
{
	char	*pwd;

	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			pwd = ft_strdup(env->value);
			if (!pwd)
				return (catch()->error_msg
					= "Memory allocation failed for ft_getcwd\n", NULL);
			return (pwd);
		}
		env = env->next;
	}
	return (NULL);
}
