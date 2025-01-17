/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:08:15 by joafern2          #+#    #+#             */
/*   Updated: 2025/01/16 03:58:44 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	char	**arg;

	arg = cmd->arg;
	if (ft_strncmp(arg[1], "-n", 3) == 0)
		n_flag = 1;
	else
		n_flag = 0;
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
	printf("é daqui sim!\n");
	return (1);
}
