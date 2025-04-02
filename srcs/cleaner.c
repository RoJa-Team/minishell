/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:14:19 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/02 22:18:28 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clean_env(void)
{
	int		i;
	t_env	*temp;

	while (ms()->env_lst != NULL)
	{
		// debug("clean env_lst", (void *)ms()->env_lst);
		temp = ms()->env_lst;
		ms()->env_lst = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	i = 0;
	while (ms()->ms_env && ms()->ms_env[i])
	{
		// debug("clean ms_env", i);
		free(ms()->ms_env[i]);
		i++;
	}
	free(ms()->ms_env);
	ms()->ms_env = NULL;
}

void	clean_cmd(void)
{
	int	i;
	int	j;

	i = 0;
	while (ms()->cmd && ms()->cmd[i])
	{
		j = 0;
		while (ms()->cmd[i]->arg && ms()->cmd[i]->arg[j])
		{
			free(ms()->cmd[i]->arg[j]);
			j++;
		}
		free(ms()->cmd[i]->arg);
		free_list(ms()->cmd[i]->fd_in, get_offset(&dummy()->redir, \
		&dummy()->redir.next));
		free_list(ms()->cmd[i]->fd_out, get_offset(&dummy()->redir, \
		&dummy()->redir.next));
		free(ms()->cmd[i]);
		i++;
	}
	free(ms()->cmd);
}

void	clean_structs(void)
{
	// debug("clean_structs", "");
	clean_env();
	clean_cmd();
}