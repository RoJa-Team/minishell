/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:12:08 by joafern2          #+#    #+#             */
/*   Updated: 2025/01/15 22:38:10 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

extern char **environ; // real environment

int	is_builtin(char **arg)
{
	(void)arg;
	return (0);	
}

char	*find_path(char *cmd)
{
	char	*path_env = getenv("PATH"); // using real env
	char	**path_dir;
	char	*full_path;
	char	*temp;
	int	i;

	i = 0;
	if (!path_env)
		return (NULL);
	path_dir = ft_split(path_env, ':');
	if (!path_dir)
		deallocate("Failed to split $PATH\n");
	while (path_dir[i])
	{
		temp = ft_strjoin(path_dir[i], "/");
		full_path = ft_strjoin(temp, cmd);
		if (!full_path)
			deallocate("Failed to join command to $PATH\n");
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(temp);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(t_ms *ms)
{
	int	i;
	char	*cmd;
	char	**arg;
	char	*path;

	i = 0;
	while (ms->cmd[i])
	{
		cmd = ms->cmd[i]->arg[0];
		arg = ms->cmd[i]->arg;
		if (is_builtin(arg) == 1)
		{
			i++;
			continue ;
		}
		else if (fork() == 0)
		{
			path = find_path(cmd);
			if (!path)
				deallocate("$PATH for command not found\n"); 
			if (execve(path, arg, environ) == -1) // real env in use
			{
				deallocate("Error executing execve.\n");
				free(path);
			}
			free(path);
		}
		else
			wait(NULL);
		i++;
	}
}

int	main()
{
	t_ms	ms;
	static char *args1[] = {"echo", "hello world", NULL};
	static char *args2[] = {"la", "-a", NULL};

	int cmd_count = 2;

	ms.cmd = malloc(sizeof(t_cmd*) * (cmd_count + 1));
	for (int i = 0; i < cmd_count; i++)
		ms.cmd[i] = malloc(sizeof(t_cmd));
	
	ms.cmd[0]->arg = args1;
	ms.cmd[1]->arg = args2;
	ms.cmd[cmd_count] = NULL;

	exec_cmd(&ms);
	
	for (int i = 0; i < cmd_count; i++)
		free(ms.cmd[i]);	
	free(ms.cmd);

	return (0);
}
