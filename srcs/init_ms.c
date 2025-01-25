/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:49:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/24 22:38:20 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	copy_env(t_ms *ms, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	ms->ms_env = malloc(sizeof(char *) * i + 1);
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
}

t_ms	*init_ms(char **env)
{
	t_ms *ms;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		deallocate("Error> failed memory allocation for t_ms.");
	ms->cmd = NULL;
	ms->env_lst = NULL;
	ms->parse = NULL;
	copy_env(ms, env);
	return (ms);
}
