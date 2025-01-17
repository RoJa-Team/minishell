/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 03:08:15 by joafern2          #+#    #+#             */
/*   Updated: 2025/01/17 18:44:33 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**split_env_var(t_ms *ms)
{
	int	i;
	char	**env;

	i = 0;
	while (ms->env[i])

}

void	is_env_var(t_ms *ms, int i)
{
	int	j;
	int	h;
	char	**arg;

	h = 0;
	arg = ms->cmd[i]->arg;
	while (arg[h])
	{
		j = 0;
		while (ft_strcmp(arg[h], ms->env[j]) != 0 && arg[j])
			j++;
		
		h++;
	}
}

int	ft_echo(t_ms *ms)
{
	int	i;
	int	n_flag;
	char	**arg;
	int	fd = 1; // temporary implementation

	arg = ms->cmd->arg;
	if (ft_strncmp(arg[1], "-n", 3) == 0)
		n_flag = 1;
	else
		n_flag = 0;
	i = n_flag + 1;
	while (arg[i])
	{
		is_env_var(ms, i);
		ft_putstr_fd(arg[i], fd);
		if (arg[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	printf("é daqui sim!\n");
	return (1);
}
