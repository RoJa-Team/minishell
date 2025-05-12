/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:55:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/12 14:22:39 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_parent_dir(char *ab_path)
{
	int		i;
	char	*temp;

	temp = ft_strdup(ab_path);
	if (!temp)
		return (catch()->error_msg = "Strdup failed", NULL);
	i = ft_strlen(temp);
	while (i > 0 && temp[i] != '/')
		i--;
	if (i == 0)
	{
		free(temp);
		temp = ft_calloc(sizeof(char), 2);
		temp[i] = '/';
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*get_ab_path(char *ab_path, char *next_dir)
{
	char	**split_path;

	if (!ab_path)
		return (catch()->error_msg = "memory allocation fail.\n", NULL);
	if (next_dir[ft_strlen(next_dir) - 1] == '/')
		next_dir[ft_strlen(next_dir) - 1] = '\0';
	if (next_dir[0] == '/')
	{
		free(ab_path);
		ab_path = ft_strdup(next_dir);
		if (!ab_path)
			return (catch()->error_msg = "strdup failed\n", NULL);
	}
	else
	{
		split_path = ft_split(next_dir, '/');
		if (!split_path)
			return (free(ab_path), catch()->error_msg = "split failed\n", NULL);
		if (strncmp(ab_path, "/", 2) == 0 && ft_strncmp(next_dir, ".", 2) != 0)
			ab_path[0] = '\0';
		ab_path = cd_cases(split_path, ab_path, NULL, 0);
	}
	if (catch()->error_msg != NULL)
		return (free(ab_path), NULL);
	return (ab_path);
}

char	*get_home(t_env *env, t_cmd *cmd)
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
				if (!temp->value)
					return (NULL);
				home = ft_strdup(temp->value);
				if (!home)
					return (catch()->error_msg = "strdup failed\n", NULL);
				return (home);
			}
			else
				break ;
		}
		temp = temp->next;
	}
	ft_putstr_fd("cd: HOME not set\n", 2);
	cmd->cmd_status = 1;
	return (NULL);
}

char	*check_pwd(char *oldpwd)
{
	struct stat	st;

	while (!oldpwd)
	{
		oldpwd = get_parent_dir(ms()->exec->pwd);
		if (catch()->error_msg)
			deallocate();
		free(ms()->exec->pwd);
		ms()->exec->pwd = oldpwd;
		if (stat(oldpwd, &st) == 0)
			break ;
		oldpwd = NULL;
	}
	return (oldpwd);
}
