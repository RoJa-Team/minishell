/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:00:32 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/07 21:41:58 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execute_builtin_or_execve(int i)
{
	if (is_builtin(i))
	{
		execute_builtin(i);
		clean_structs();
		exit(ms()->cmd[i]->exit_status);
	}
	else
		execute_execve(i);
}

int	is_executable(const char *path)
{
	struct stat	st;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	return (1);
}

void	remove_key(t_env *prev, t_env *temp, char *arg)
{
	(void)arg;
	while (temp != NULL)
	{
		if (ft_strncmp(arg, temp->key, ft_strlen(temp->key) + 1) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				ms()->env_lst = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	wait_for_childs(void)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (ms()->cmd[i] && waitpid(ms()->cmd[i]->pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			ms()->cmd[i]->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms()->cmd[i]->exit_status = 128 + WTERMSIG(status);
		if (ms()->cmd[i]->exit_status == 130)
			write(1, "\n", 1);
		i++;
	}
}

void	not_found_case(int i)
{
	struct stat	st;

	if (access(ms()->cmd[i]->arg[0], F_OK) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		clean_structs();
		exit(127);
	}
	else if ((access(ms()->cmd[i]->arg[0], R_OK) == -1
			|| access(ms()->cmd[i]->arg[0], W_OK) == -1))
		ft_putstr_fd(": Permission denied\n", 2);
	else if (!S_ISREG(st.st_mode))
		ft_putstr_fd(": Is a directory\n", 2);
	clean_structs();
	exit (126);
}
