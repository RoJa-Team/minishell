/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:00:17 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/14 04:29:27 by rafasant         ###   ########.fr       */
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

	// t_cmd	*ll_cmd;
	// t_parse	*ll_token;
	// int	i;
	// int	j;

	// ll_cmd = ms->cmds;
	// i = 0;
	// while (ll_cmd != NULL)
	// {
	// 	ll_token = ll_cmd->token;
	// 	j = 0;
	// 	while (ll_token != NULL)
	// 	{
	// 		ft_printf("ll_cmd[%d][%d]: %s\n", i, j, ll_token->token);
	// 		ll_token = ll_token->next;
	// 		j++;
	// 	}
	// 	i++;
	// 	ll_cmd = ll_cmd->next;
	// }
}