/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:12:08 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/09 20:18:52 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(int i)
{
	char	**arg;

	arg = ms()->cmd[i]->arg;
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
	else if (ft_strncmp(arg[0], "exit", 5) == 0)
		return (1);
	return (0);
}

void	execute_builtin(int i)
{
	char	**arg;
	int		save_out;

	arg = ms()->cmd[i]->arg;
	if (ft_strncmp(arg[0], "exit", 5) == 0)
		ft_exit(i);
	save_out = dup(STDOUT_FILENO);
	if (ft_strncmp(arg[0], "echo", 5) == 0)
		ft_echo(i);
	else if (ft_strncmp(arg[0], "cd", 3) == 0)
		ft_cd(i);
	else if (ft_strncmp(arg[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(arg[0], "export", 7) == 0)
		ft_export(i);
	else if (ft_strncmp(arg[0], "unset", 6) == 0)
		ft_unset(i);
	else if (ft_strncmp(arg[0], "env", 4) == 0)
		ft_env(i);
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
}

void	exec_cmd(void)
{
	int	i;
	int	save_stdin;
	int	save_stdout;

	ms()->exec = malloc(sizeof(t_exec));
	if (!ms()->exec)
		deallocate("Memory allocation error: exec_cmd\n");
	ms()->exec->prev_fd = -1;
	//save_and_restore_std(&save_stdin, &save_stdout, 1);
	i = 0;
	while (ms()->cmd[i])
	{
		handle_input(&i, &save_stdin, &save_stdout);
		i++;
	}
	//save_and_restore_std(&save_stdin, &save_stdout, 2);
	//ft_printf("Exit status : %d\n", ms()->exit_status);
	free(ms()->exec);
	while (wait(NULL) > 0)
		continue ;
}

void	handle_input(int *i, int *save_stdin, int *save_stdout)
{
	int		*prev_fd;
	int		fd[2];
	int		status;
	pid_t	pid;

	(void)save_stdin;
	(void)save_stdout;
	prev_fd = &ms()->exec->prev_fd;
	if (is_builtin(*i) == 1 && !ms()->cmd[*i + 1])
	{
		if (ms()->cmd[*i]->fd_in || ms()->cmd[*i]->fd_out)
		{
			save_and_restore_std(save_stdin, save_stdout, 1);
			if (handle_redirections(ms()->cmd[*i]) == 0)
				execute_builtin(*i);
			save_and_restore_std(save_stdin, save_stdout, 2);
		}
		else
			execute_builtin(*i);
		return ;
	}
	if (ms()->cmd[*i + 1])
		pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		child_process(*prev_fd, fd, *i);
	close_pipe(fd, prev_fd, *i);
	close_heredoc();
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			ms()->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms()->exit_status = 128 + WTERMSIG(status);
	}
}

void	close_heredoc(void)
{
	int		i;
	int		fd;
	t_redir	*r;

	i = 0;
	while (ms()->cmd && ms()->cmd[i])
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

void	child_process(int prev_fd, int *fd, int i)
{
	int	res;

	res = 0;
	if (ms()->cmd[i]->fd_in || ms()->cmd[i]->fd_out)
		res = handle_redirections(ms()->cmd[i]);
	if (res != 0)
		return ;
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
	if (is_builtin(i))
	{
		execute_builtin(i);
		free(ms()->exec);
		clean_structs();
		exit (0);
	}
	else
		execute_execve(i);
}

void	execute_execve(int i)
{
	char	*path;

	path = NULL;
	if (ms()->cmd[i]->arg[0][0] != '/' && \
	(ft_strncmp((ms()->cmd[i])->arg[0], "./", 2) != 0))
		path = find_path(ms()->env_lst, ms()->cmd[i]->arg[0]);
	else
		if (access(ms()->cmd[i]->arg[0], X_OK) == 0)
			path = ms()->cmd[i]->arg[0];
	if (!path)
	{
		write(2, ms()->cmd[i]->arg[0], ft_strlen(ms()->cmd[i]->arg[0]));
		write(2, ": command not found\n", 20);
		ms()->exit_status = 127;
		free(ms()->exec);
		clean_structs();
		exit(127);
	}
	if (execve(path, ms()->cmd[i]->arg, ms()->ms_env) == -1)
		deallocate("Error executing execve: execute_execve\n");
}
