/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:36:25 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/06 20:23:46 by joafern2         ###   ########.fr       */
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
	t_parse	*temp;

	while (ms->parse != NULL)
	{
		temp = ms->parse;
		ms->parse = temp->next;
		free(temp->token);
	}
}

void	clean_cmd(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (ms->cmd[i])
	{
		j = 0;
		while (ms->cmd[i]->arg[j])
		{
			free(ms->cmd[i]->arg[j]);
			j++;
		}
		free(ms->cmd[i]);
		i++;
	}
	free(ms->cmd);
}

void	deallocate(char *message)
{
	exit(ft_printf(message));
}
