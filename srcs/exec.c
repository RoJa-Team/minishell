/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:12:08 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/09 21:47:23 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(int i)
{
	char	**arg;

	arg = ms()->cmd[i]->arg;
	if (arg)
	{
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
	}
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

	ms()->exec->prev_fd = -1;
	i = 0;
	setup_exec();
	while (ms()->cmd[i])
	{
		handle_input(&i, &save_stdin, &save_stdout);
		i++;
	}
	close_heredoc(i);
	wait_for_childs();
	if (catch()->error_msg != NULL)
		deallocate(catch()->error_msg);
	i = 0;
	while (ms()->cmd[i])
		ms()->exit_status = ms()->cmd[i++]->cmd_status;
}

void	handle_input(int *i, int *save_stdin, int *save_stdout)
{
	int	*prev_fd;

	prev_fd = &ms()->exec->prev_fd;
	if (is_builtin(*i) == 1 && !ms()->cmd[*i + 1])
	{
		if (check_redir_input(ms()->cmd[*i]->redir)
			|| check_redir_output(ms()->cmd[*i]->redir))
		{
			save_and_restore_std(save_stdin, save_stdout, 1);
			if (handle_redirections(ms()->cmd[*i]) == 0 && ms()->cmd[*i]->arg)
				execute_builtin(*i);
			save_and_restore_std(save_stdin, save_stdout, 2);
		}
		else
			execute_builtin(*i);
		if (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}
	}
	else
		fork_child_process(i, prev_fd);
}

void	fork_child_process(int *i, int *prev_fd)
{
	if (ms()->cmd[*i + 1])
		pipe(ms()->cmd[*i]->fd);
	ms()->cmd[*i]->pid = fork();
	if (ms()->cmd[*i]->pid == -1)
		return ;
	if (ms()->cmd[*i]->pid == 0)
		child_process(*prev_fd, ms()->cmd[*i]->fd, *i, -1);
	close_pipe(ms()->cmd[*i]->fd, prev_fd, *i);
}
