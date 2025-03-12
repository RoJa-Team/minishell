/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:08:15 by joafern2          #+#    #+#             */
/*   Updated: 2025/02/26 20:07:03 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_echo(t_ms *ms, int j)
{
	int	i;
	int	n_flag;
	char	**arg;
	int	fd = 1; // temporary implementation

	arg = ms->cmd[j]->arg;
	if (!arg)
		deallocate("Memory allocation failure\n");
	n_flag = 0;
	if (arg[1] && ft_strncmp(arg[1], "-n", 3) == 0)
		n_flag = 1;
	i = n_flag + 1;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		if (arg[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	free_args(arg);
}
