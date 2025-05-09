/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:20:25 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/09 21:04:41 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	child_process(int prev_fd, int *fd, int i, int res)
{
	if (ms()->cmd[i]->redir && \
	handle_redirections(ms()->cmd[i]) != 0)
		res = 1;
	if (res == 1 || !ms()->cmd[i]->arg)
	{
		if (ms()->cmd[i + 1])
			close(fd[0]);
		close_pipe(ms()->cmd[i]->fd, &prev_fd, i);
		clean_structs();
		if (res != 1)
			res = 0;
	}
	if (res != -1)
		exit(res);
	if (prev_fd != -1 && check_redir_input(ms()->cmd[i]->redir) == 0)
		dup2(prev_fd, STDIN_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (ms()->cmd[i + 1] && check_redir_output(ms()->cmd[i]->redir) == 0)
		check_next_pipe(i, fd);
	if (ms()->cmd[i + 1])
		close(fd[0]);
	close_pipe(ms()->cmd[i]->fd, &prev_fd, i);
	close_heredoc(i);
	execute_builtin_or_execve(i);
}

void	check_next_pipe(int i, int *fd)
{
	int	null_fd;

	if (!is_builtin(i + 1))
		dup2(fd[1], STDOUT_FILENO);
	else
	{
		null_fd = open("/dev/null", O_WRONLY);
		if (null_fd != -1)
		{
			dup2(null_fd, STDOUT_FILENO);
			close(null_fd);
		}
	}
}

void	not_found(int i)
{
	struct stat	st;

	if (ms()->cmd[i] && ms()->cmd[i]->arg)
		write(2, ms()->cmd[i]->arg[0], ft_strlen(ms()->cmd[i]->arg[0]));
	if (ft_strncmp(ms()->cmd[i]->arg[0], ".", 2) == 0)
	{
		ft_putstr_fd(": filename argument required\n", 2);
		clean_structs();
		exit (2);
	}
	else if (ft_strncmp(ms()->cmd[i]->arg[0], "/", 1) == 0
		|| ft_strncmp(ms()->cmd[i]->arg[0], "./", 2) == 0)
		not_found_case(i);
	else if (stat(ms()->cmd[i]->arg[0], &st) == 0
		&& ms()->cmd[i]->arg[0][strlen(ms()->cmd[i]->arg[0]) - 1] == '/')
	{
		write(2, ": Is a directory\n", 17);
		clean_structs();
		exit(126);
	}
	write(2, ": command not found\n", 20);
	clean_structs();
	exit(127);
}

void	execute_execve(int i)
{
	char	*path;

	path = NULL;
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
		r = ms()->cmd[i]->redir;
		while (r)
		{
			if (r->type == INPUT && r->operator == HEREDOC)
			{
				fd = ft_atoi(r->file[0]);
				if (fd >= 0)
					close(fd);
			}
			r = r->next;
		}
		i++;
	}
}
