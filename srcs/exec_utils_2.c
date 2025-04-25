/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:20:25 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/23 21:22:07 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	child_process(int prev_fd, int *fd, int i)
{
	if (ms()->cmd[i]->fd_in || ms()->cmd[i]->fd_out)
	{
		if (handle_redirections(ms()->cmd[i]) != 0 || !ms()->cmd[i]->arg
			|| !ms()->cmd[i]->arg[0])
		{
			clean_structs();
			exit (1);
		}
	}
	if (prev_fd != -1 && ms()->cmd[i]->fd_in == NULL)
		dup2(prev_fd, STDIN_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (ms()->cmd[i + 1] && ms()->cmd[i]->fd_out == NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (ms()->cmd[i + 1])
	{
		close(fd[1]);
		close(fd[0]);
	}
	close_heredoc(i);
	execute_builtin_or_execve(i);
}

void	invoke_shell(int i, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(path, ms()->cmd[i]->arg, ms()->ms_env) == -1)
			deallocate("Error executing execve: execute_execve\n");
	}
	else
		waitpid(pid, NULL, 0);
}

void	not_found(int i)
{
	if (ms()->cmd[i] && ms()->cmd[i]->arg)
		write(2, ms()->cmd[i]->arg[0], ft_strlen(ms()->cmd[i]->arg[0]));
	write(2, ": command not found\n", 20);
	ms()->exit_status = 127;
	clean_structs();
	exit(127);
}

void	execute_execve(int i)
{
	char				*path;
	struct sigaction	sa;

	path = NULL;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (ms()->cmd[i]->arg && ms()->cmd[i]->arg[0]
		&& (ms()->cmd[i]->arg[0][0] != '/')
		&& (ft_strncmp((ms()->cmd[i])->arg[0], "./", 2) != 0))
		path = find_path(ms()->env_lst, ms()->cmd[i]->arg[0]);
	else
	{
		if (ms()->cmd[i]->arg && ms()->cmd[i]->arg[0]
			&& access(ms()->cmd[i]->arg[0], X_OK) == 0)
			path = ms()->cmd[i]->arg[0];
	}
	if (!path || execve(path, ms()->cmd[i]->arg, ms()->ms_env) == -1)
		not_found(i);
}

void	close_heredoc(int i)
{
	int		fd;
	t_redir	*r;

	i = 0;
	while (ms()->cmd[i])
	{
		r = ms()->cmd[i]->fd_in;
		while (r)
		{
			if (r->type == 2)
			{
				fd = ft_atoi(r->file);
				if (fd >= 0)
					close(fd);
			}
			r = r->next;
		}
		i++;
	}
}
