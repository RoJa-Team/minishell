/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:14:19 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/03 20:20:52 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clean_env(void)
{
	int		i;
	t_env	*temp;

	while (ms()->env_lst != NULL)
	{
		temp = ms()->env_lst;
		ms()->env_lst = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	i = 0;
	while (ms()->ms_env && ms()->ms_env[i])
	{
		free(ms()->ms_env[i]);
		i++;
	}
	free(ms()->ms_env);
	ms()->ms_env = NULL;
}

void	clean_redir(void)
{
	int		i;
	t_redir	*temp;

	i = 0;
	while (ms()->cmd && ms()->cmd[i])
	{
		while (ms()->cmd[i]->fd_in != NULL)
		{
			temp = ms()->cmd[i]->fd_in;
			ms()->cmd[i]->fd_in = temp->next;
			free(temp->file);
			free(temp);
		}
		while (ms()->cmd[i]->fd_out != NULL)
		{
			temp = ms()->cmd[i]->fd_out;
			ms()->cmd[i]->fd_out = temp->next;
			free(temp->file);
			free(temp);
		}
		i++;
	}
}

void	clean_cmd(void)
{
	int	i;
	int	j;

	i = 0;
	clean_redir();
	while (ms()->cmd && ms()->cmd[i])
	{
		j = 0;
		while (ms()->cmd[i]->arg && ms()->cmd[i]->arg[j])
		{
			free(ms()->cmd[i]->arg[j]);
			j++;
		}
		free(ms()->cmd[i]->arg);
		free(ms()->cmd[i]);
		i++;
	}
	free(ms()->cmd);
	ms()->cmd = NULL;
}

void	clean_structs(void)
{
	clean_env();
	if (ms()->cmd)
		clean_cmd();
}