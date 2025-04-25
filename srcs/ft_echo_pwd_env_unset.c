/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_pwd_env_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:08:15 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/22 19:23:22 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_echo(int j)
{
	int		i;
	int		n_flag;
	char	**arg;

	arg = ms()->cmd[j]->arg;
	if (!arg)
		return ((void)(catch()->error_msg = "Memory allocation failure\n"));
	n_flag = 0;
	if (arg[1] && ft_strncmp(arg[1], "-n", 3) == 0)
		n_flag = 1;
	i = n_flag + 1;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	ms()->exit_status = 0;
}

void	ft_env(int i)
{
	int		j;
	int		fd;
	char	**arg;

	fd = STDOUT_FILENO;
	j = 0;
	arg = ms()->cmd[i]->arg;
	if (arg[1])
	{
		ft_printf("env: '%s: No such file or directory\n", arg[1]);
		ms()->exit_status = 1;
	}
	else
	{
		while (ms()->ms_env[j])
		{
			ft_putstr_fd(ms()->ms_env[j], fd);
			ft_putchar_fd('\n', fd);
			j++;
		}
		ms()->exit_status = 0;
	}
}

void	ft_pwd(void)
{
	ft_putstr_fd(ms()->exec->pwd, 1);
	ft_putchar_fd('\n', 1);
	ms()->exit_status = 0;
}

void	ft_unset(int i)
{
	t_env	*temp;
	t_env	*prev;
	char	**arg;
	int		j;

	j = 1;
	arg = ms()->cmd[i]->arg;
	temp = ms()->env_lst;
	if (!temp || !temp->key)
		return ;
	while (arg[j])
	{
		prev = NULL;
		temp = ms()->env_lst;
		remove_key(prev, temp, arg[j]);
		j++;
	}
	update_ms_env();
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
			ms()->exit_status = 0;
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	ms()->exit_status = 1;
}
