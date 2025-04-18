/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:41:46 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/17 19:07:33 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_ll_overflow(const char *str)
{
	int				sign;
	int				i;
	unsigned long	res;

	sign = 1;
	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		if ((sign == 1 && res > LLONG_MAX) || (sign == -1 && \
			res > (unsigned long)LLONG_MAX + 1))
			return (1);
		i++;
	}
	return (0);
}

void	cleanup(void)
{
	//free(ms()->exec->pwd);
	//free(ms()->exec);
	clean_structs();
}

void	ft_exit(int i)
{
	char	**arg;

	arg = ms()->cmd[i]->arg;
	if (!arg[1])
		ft_putendl_fd("exit", STDERR_FILENO);
	if (arg[1])
	{
		if (!is_numeric(arg[1]) || is_ll_overflow(arg[1]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(arg[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			cleanup();
			exit(2);
		}
		else if (arg[2])
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			ms()->exit_status = 1;
			return ;
		}
		else
			ms()->exit_status = (unsigned char)ft_atoi(arg[1]);
	}
	cleanup();
	exit (ms()->exit_status);
}
