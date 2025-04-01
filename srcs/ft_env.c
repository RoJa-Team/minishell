/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:47:29 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/01 18:37:19 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_env(int i)
{
	int		j;
	int		fd;
	char	**arg;

	fd = STDOUT_FILENO;
	j = 0;
	arg = ms()->cmd[i]->arg;
	if (arg[1])
		ft_printf("env: '%s: No such file or directory\n", arg[1]);
	else
	{
		while (ms()->ms_env[j])
		{
			ft_putstr_fd(ms()->ms_env[j], fd);
			ft_putchar_fd('\n', fd);
			j++;
		}
	}
}
