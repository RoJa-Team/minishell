/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:10:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/22 18:57:10 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	close_pipe(int *fd, int *prev_fd, int i)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (ms()->cmd[i + 1])
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
}

void	save_and_restore_std(int *save_stdin, int *save_stdout, int flag)
{
	if (flag == 1)
	{
		*save_stdout = dup(STDOUT_FILENO);
		*save_stdin = dup(STDIN_FILENO);
		if (*save_stdout == -1 || *save_stdin == -1)
			return ((void)(catch()->error_msg
				= "FD duplication error: save_and_restore_std\n"));
	}
	else if (flag == 2)
	{
		if (*save_stdout != -1)
		{
			dup2(*save_stdout, STDOUT_FILENO);
			close(*save_stdout);
			*save_stdout = -1;
		}
		if (*save_stdin != -1)
		{
			dup2(*save_stdin, STDIN_FILENO);
			close(*save_stdin);
			*save_stdin = -1;
		}
	}
}

char	*get_value(t_env *env, char *key)
{
	t_env	*temp;
	char	*value;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (temp->invis == 0)
			{
				value = ft_strdup(temp->value);
				if (!value)
					return (NULL);
				else
					return (value);
			}
			else
				return (NULL);
		}
		temp = temp->next;
	}
	return (NULL);
}

char	*get_full_path(char *path_dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path_dir, "/");
	if (!temp)
		return (catch()->error_msg = "Memory allocation error\n");
	full_path = ft_strjoin(temp, cmd);
	if (!full_path)
		return (free(temp), catch()->error_msg
			= "Memory allocation error: get_full_path\n");
	free(temp);
	if (is_executable(full_path) == 1)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_path(t_env *env_lst, char *cmd)
{
	char	*path_env;
	char	**path_dir;
	char	*full_path;
	int		i;

	(void)env_lst;
	i = 0;
	path_env = get_value(env_lst, "PATH");
	if (!path_env)
		return (catch()->error_msg = "Missing PATH env var", NULL);
	path_dir = ft_split(path_env, ':');
	free(path_env);
	if (!path_dir)
		return (catch()->error_msg
			= "Memory allocation error: find_path\n", NULL);
	while (path_dir[i])
	{
		full_path = get_full_path(path_dir[i], cmd);
		if (full_path != NULL)
			break ;
		free(path_dir[i]);
		i++;
	}
	free(path_dir);
	return (full_path);
}
