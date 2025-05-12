/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:14:19 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 12:42:37 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clean_env_lst(void)
{
	t_env	*temp;

	while (ms()->env_lst != NULL)
	{
		temp = ms()->env_lst;
		ms()->env_lst = temp->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	clean_ms_env(void)
{
	int	i;

	i = 0;
	while (ms()->ms_env && ms()->ms_env[i])
	{
		free(ms()->ms_env[i]);
		i++;
	}
	if (ms()->ms_env)
		free(ms()->ms_env);
	ms()->ms_env = NULL;
}

void	clean_redir(void)
{
	int		i;
	int		j;
	t_redir	*temp;

	i = 0;
	while (ms()->cmd && ms()->cmd[i])
	{
		while (ms()->cmd[i]->redir != NULL)
		{
			j = 0;
			temp = ms()->cmd[i]->redir;
			ms()->cmd[i]->redir = temp->next;
			while (temp->file && temp->file[j])
				free(temp->file[j++]);
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
	clean_parse();
	if (ms()->env_lst)
		clean_env_lst();
	if (ms()->ms_env)
		clean_ms_env();
	if (ms()->cmd)
		clean_cmd();
	if (ms()->exec)
	{
		if (ms()->exec->pwd)
			free(ms()->exec->pwd);
		free(ms()->exec);
	}
	rl_clear_history();
}
