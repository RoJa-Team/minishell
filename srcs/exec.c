/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:12:08 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/26 20:02:08 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(t_ms *ms, int i)
{
	char	**arg;

	arg = ms->cmd[i]->arg;
	if (ft_strncmp(arg[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(arg[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(arg[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(arg[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(arg[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(arg[0], "env", 4) == 0)
		return (1);
	/*
	else if (arg[0] == "exit")
		ft_exit(ms);
	*/
	return (0);
}

void	execute_builtin(t_ms *ms, int i)
{
	char	**arg;
	int		save_out;

	save_out = dup(STDOUT_FILENO);
	arg = ms->cmd[i]->arg;
	if (ft_strncmp(arg[0], "echo", 5) == 0)
		ft_echo(ms, i);
	else if (ft_strncmp(arg[0], "cd", 3) == 0)
		ft_cd(ms, i);
	else if (ft_strncmp(arg[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(arg[0], "export", 7) == 0)
		ft_export(ms, i);
	else if (ft_strncmp(arg[0], "unset", 6) == 0)
		ft_unset(ms, i);
	else if (ft_strncmp(arg[0], "env", 4) == 0)
		ft_env(ms, i);
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
	/*
	else if (arg[0] == "exit")
		ft_exit(ms);
	*/
}

void	exec_cmd(t_ms *ms)
{
	int	i;
	int	save_stdout;
	int	save_stdin;

	ms->exec = malloc(sizeof(t_exec));
	if (!ms->exec)
		deallocate("Memory allocation fail.\n");
	ms->exec->prev_fd = -1;
	save_and_restore_std(&save_stdin, &save_stdout, 1);
	i = 0;
	while (ms->cmd[i])
	{
		handle_input(ms, &i, &save_stdin, &save_stdout);
		i++;
	}
	save_and_restore_std(&save_stdin, &save_stdout, 2);
	while (wait(NULL) > 0)
		continue ;
}

void	handle_input(t_ms *ms, int *i, int *save_stdin, int *save_stdout)
{
	int		*prev_fd;
	int		fd[2];
	int		status;
	pid_t	pid;

	(void)save_stdin;
	(void)save_stdout;
	prev_fd = &ms->exec->prev_fd;
	if (is_builtin(ms, *i) == 1 && !ms->cmd[*i + 1])
	{
		if (ms->cmd[*i]->fd_in || ms->cmd[*i]->fd_out)
			handle_redirections(ms->cmd[*i]);
		execute_builtin(ms, *i);
		return ;
	}
	if (ms->cmd[*i + 1])
		pipe(fd);
	pid = fork();
	if (pid == 0)
		child_process(ms, *prev_fd, fd, *i);
	close_pipe(ms, fd, prev_fd, *i);
	waitpid(pid, &status, 0);
	if ((status & 0xFF) == 127)
		return ;
}

void	child_process(t_ms *ms, int prev_fd, int *fd, int i)
{
	if (ms->cmd[i]->fd_in || ms->cmd[i]->fd_out)
		handle_redirections(ms->cmd[i]);
	if (prev_fd != -1 && ms->cmd[i]->fd_in == NULL)
		dup2(prev_fd, STDIN_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (ms->cmd[i + 1] && ms->cmd[i]->fd_out == NULL)
		dup2(fd[1], STDOUT_FILENO);
	if (ms->cmd[i + 1])
	{
		close(fd[1]);
		close(fd[0]);
	}
	if (is_builtin(ms, i))
	{
		execute_builtin(ms, i);
		exit (0);
	}
	else
		execute_execve(ms, i);
}

void	execute_execve(t_ms *ms, int i)
{
	char	*path;

	path = find_path(ms->env_lst, ms->cmd[i]->arg[0]);
	if (!path)
	{
		write(2, ms->cmd[i]->arg[0], ft_strlen(ms->cmd[i]->arg[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (execve(path, ms->cmd[i]->arg, ms->ms_env) == -1)
		deallocate("Error executing execve.\n");
}
