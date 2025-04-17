/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:49:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/17 19:08:20 by joafern2         ###   ########.fr       */
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
		deallocate("Memory allocation error: copy_env\n");
	i = 0;
	while (env[i])
	{
		ms()->ms_env[i] = ft_strdup(env[i]);
		if (!ms()->ms_env[i])
			deallocate("Memory allocation error: copy_env\n");
		i++;
	}
	ms()->ms_env[i] = NULL;
}

void	create_env_lst(void)
{
	int		i;
	t_env	*new_env;
	t_env	*temp;

	i = -1;
	while (ms()->ms_env[++i] != NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			deallocate("Memory allocation error: create_env_lst\n");
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

void	init(char **env)
{
	ms()->cmd = NULL;
	ms()->env_lst = NULL;
	ms()->exit_status = 0;
	ms()->exec = malloc(sizeof(t_exec));
	if (!ms()->exec)
		deallocate("Memory allocation error: exec_cmd\n");
	ms()->exec->pwd = NULL;
	ms()->nested_shell = 0;	
	copy_env(env);
	create_env_lst();
	parse()->cmd_ll = NULL;
	parse()->arg_ll = NULL;
}
