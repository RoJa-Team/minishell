/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:10:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/02 20:06:06 by joafern2         ###   ########.fr       */
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
			deallocate("dup failed'\n");
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
	else if (flag == 3)
	{
		if (*save_stdout != -1)
		{
			ft_printf("closinf std out\n");
			close(*save_stdout);
		}
		if (*save_stdin != -1)
		{
			close(*save_stdin);
			ft_printf("closinf std out\n");
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
	full_path = ft_strjoin(temp, cmd);
	if (!full_path)
		deallocate("Failed to join command to $PATH\n");
	if (access(full_path, X_OK) == 0)
	{
		free(temp);
		free(path_dir);
		return (full_path);
	}
	free(temp);
	free(full_path);
	free(path_dir);
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
		return (NULL);
	path_dir = ft_split(path_env, ':');
	if (!path_dir)
		deallocate("Failed to split $PATH\n");
	while (path_dir[i])
	{
		full_path = get_full_path(path_dir[i], cmd);
		if (full_path != NULL)
			return (full_path);
		i++;
	}
	free(path_dir);
	return (NULL);
}
