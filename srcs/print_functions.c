/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:00:17 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/24 20:15:00 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_ms_env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->ms_env[i])
	{
		ft_printf("> %s\n", ms->ms_env[i]);
		i++;
	}
}

void	print_env_lst(t_ms *ms)
{
	t_env	*temp;

	temp = ms->env_lst;
	while (temp != NULL)
	{
		ft_printf("Key: %s - Value: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	print_cmd(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (ms->cmd[i])
	{
		j = 0;
		while (ms->cmd[i]->arg[j])
		{
			ft_printf("%d.%d> %s\n", i, j, ms->cmd[i]->arg[j]);
			j++;
		}
		i++;
	}
}

void	printInt(char *info, int data) //TODO remove this
{
	ft_printf("\n%s: >%d<\n", info, data);
}

void	printString(char *info, char *data) //TODO remove this
{
	ft_printf("\n%s: >%s<\n", info, data);
}