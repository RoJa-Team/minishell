/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:47:29 by joafern2          #+#    #+#             */
/*   Updated: 2025/02/10 22:21:54 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_env(t_ms *ms, int i)
{
	int	j;
	int	fd = 1;
	char	**arg;

	j = 0;
	arg = ms->cmd[i]->arg;
	if (arg[1])
		ft_printf("env: '%s: No such file or directory\n", arg[1]);
	else
	{
		while (ms->ms_env[j])
		{
			ft_putstr_fd(ms->ms_env[j], fd);
			ft_putchar_fd('\n', fd);
			j++;
		}
	}
	return (1);	
}
