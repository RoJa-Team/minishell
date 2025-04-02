/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:38:02 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/01 20:57:48 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_unset(int i)
{
	t_env	*temp;
	t_env	*prev;
	char	**arg;
	int		j;

	j = 1;
	arg = ms()->cmd[i]->arg;
	temp = ms()->env_lst;
	if (!temp || !temp->key)
		return ;
	while (arg[j])
	{
		prev = NULL;
		temp = ms()->env_lst;
		remove_key(prev, temp, arg[j]);
		j++;
	}
	update_ms_env();
}

void	remove_key(t_env *prev, t_env *temp, char *arg)
{
	while (temp != NULL)
	{
		if (ft_strncmp(arg, temp->key, ft_strlen(temp->key) + 1) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				ms()->env_lst = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			ms()->exit_status = 0;
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	ms()->exit_status = 1;
}
