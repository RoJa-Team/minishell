/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_pwd_env_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:08:15 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/07 21:38:18 by rafasant         ###   ########.fr       */
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
	n_flag = check_n_flag(arg);
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
}

int	check_n_flag(char **arg)
{
	int	i;

	i = 1;
	if (arg[1] && arg[1][0] == '-')
	{
		while (arg[1][i] == 'n' && arg[1][i])
			i++;
		if (arg[1][i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_env(int i)
{
	int		j;
	char	**arg;

	j = 0;
	arg = ms()->cmd[i]->arg;
	while (arg[j])
	{
		if (ft_strncmp(arg[j], "env", 4) != 0)
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ms()->cmd[i]->exit_status = 127;
			return ;
		}
		j++;
	}
	j = 0;
	while (ms()->ms_env[j])
	{
		ft_putstr_fd(ms()->ms_env[j], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		j++;
	}
}

void	ft_pwd(void)
{
	ft_putstr_fd(ms()->exec->pwd, 1);
	ft_putchar_fd('\n', 1);
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
