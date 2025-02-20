/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:36:25 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/14 04:57:59 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
}

void	clean_parse(t_ms *ms)
{
	// t_parse	*temp;

	// while (ms->parse != NULL)
	// {
	// 	temp = ms->parse;
	// 	ms->parse = temp->next;
	// 	free(temp->token);
	// }

	t_cmd	*ll_cmd;
	t_parse	*ll_token;

	ll_cmd = ms->cmds;
	while (ms->cmds != NULL)
	{
		ll_cmd = ms->cmds;
		while (ms->cmds->token != NULL)
		{
			ll_token = ms->cmds->token;
			ms->cmds->token = ll_token->next;
			free(ll_token);
		}
		ms->cmds = ll_cmd->next;
	}
}

void	clean_cmd(t_ms *ms)
{
	int	i;
	int	j;
	// t_parse	*ll_token;

	i = 0;
	while (ms->cmd[i])
	{
		j = 0;
		while (ms->cmd[i]->arg[j])
		{
			free(ms->cmd[i]->arg[j]);
			j++;
		}
		// while (ms->cmd[i]->token)
		// {
		// 	ll_token = ms->cmd[i]->token;
		// 	ms->cmd[i]->token = ll_token->next;
		// 	free(ll_token->token);
		// }
		free(ms->cmd[i]);
		i++;
	}
	free(ms->cmd);
}

void	deallocate(char *message)
{
	exit(ft_printf(message));
}
