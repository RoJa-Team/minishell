/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:38:02 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/24 19:05:57 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_unset(t_ms *ms, int i)
{
	t_env	*temp;
	t_env	*prev;
	char	**arg;
	int		j;

	j = 1;
	arg = ms->cmd[i]->arg;
	temp = ms->env_lst;
	if (!temp || !temp->key)
		return ;
	while (arg[j])
	{
		prev = NULL;
		temp = ms->env_lst;
		remove_key(ms, prev, temp, arg[j]);
		j++;
	}
	update_ms_env(ms);
}

void	remove_key(t_ms *ms, t_env *prev, t_env *temp, char *arg)
{
	while (temp != NULL)
	{
		if (ft_strncmp(arg, temp->key, ft_strlen(temp->key) + 1) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				ms->env_lst = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}
