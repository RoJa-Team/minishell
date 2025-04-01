/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:49:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/01 18:16:14 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	copy_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms()->ms_env = malloc(sizeof(char *) * (i + 1));
	if (!ms()->ms_env)
		deallocate("Error> copy_env");
	i = 0;
	while (env[i])
	{
		ms()->ms_env[i] = ft_strdup(env[i]);
		if (!ms()->ms_env[i])
			deallocate("Error> copy_env");
		i++;
	}
	ms()->ms_env[i] = NULL;
}

void	create_env_lst()
{
	int		i;
	t_env	*new_env;
	t_env	*temp;

	i = -1;
	while (ms()->ms_env[++i] != NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			deallocate("Error> create_env_lst");
		new_env->key = ft_strndup(ms()->ms_env[i], \
		ft_strlen_c(ms()->ms_env[i], '='));
		new_env->value = ft_strdup(ft_strchr(ms()->ms_env[i], '=') + 1);
		new_env->invis = 0;
		new_env->next = NULL;
		if (!ms()->env_lst)
			ms()->env_lst = new_env;
		else
		{
			temp = ms()->env_lst;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_env;
		}
	}
}

void	init_ms(char **env)
{
	ms()->cmd = NULL;
	ms()->env_lst = NULL;
	//ms->exec = NULL;
	copy_env(env);
	create_env_lst();
}
