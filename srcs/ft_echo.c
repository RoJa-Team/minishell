/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:08:15 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/01 20:48:57 by joafern2         ###   ########.fr       */
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
		deallocate("Memory allocation failure\n");
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
