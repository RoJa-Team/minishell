/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:49:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/11 21:51:02 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	copy_env(t_ms *ms, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms->ms_env = malloc(sizeof(char *) * (i + 1));
	if (!ms->ms_env)
		deallocate("Error> copy_env");
	i = 0;
	while (env[i])
	{
		ms->ms_env[i] = ft_strdup(env[i]);
		if (!ms->ms_env[i])
			deallocate("Error> copy_env");
		i++;
	}
	ms->ms_env[i] = NULL;
}

void	create_env_lst(t_ms *ms)
{
	int		i;
	char	**env;
	t_env	*new_env;
	t_env	*temp;

	i = 0;
	while (ms->ms_env[i] != NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			deallocate("Error> create_env_lst");
		env = ft_split(ms->ms_env[i], '=');
		new_env->key = ft_strdup(env[0]);
		new_env->value = NULL;
		if (env[1])
			new_env->value = ft_strdup(env[1]);
		new_env->invis = 0;
		new_env->next = NULL;
		if (!ms->env_lst)
			ms->env_lst = new_env;
		else
		{
			temp = ms->env_lst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_env;
		}
		free_array(env);
		i++;
	}
}

t_ms	*init_ms(char **env)
{
	t_ms *ms;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		deallocate("Error> failed memory allocation for t_ms.");
	ms->cmd = NULL;
	ms->cmds = NULL;
	ms->env_lst = NULL;
	copy_env(ms, env);
	create_env_lst(ms);
	return (ms);
}
