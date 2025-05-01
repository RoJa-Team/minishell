/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:49:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/26 00:00:12 by rafasant         ###   ########.fr       */
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
		return ((void)(catch()->error_msg = \
		"Memory allocation error: copy_env\n"));
	i = 0;
	while (env[i])
	{
		ms()->ms_env[i] = ft_strdup(env[i]);
		if (!ms()->ms_env[i])
			return (ms()->ms_env[i] = 0, clean_env_lst(), \
			(void)(catch()->error_msg = \
			"Memory allocation error: copy_env\n"));
		i++;
	}
	ms()->ms_env[i] = NULL;
}

void	new_env(t_env **env_node, int i)
{
	*env_node = malloc(sizeof(t_env));
	if (!env_node)
		return ((void)(clean_env_lst(), catch()->error_msg = \
		"Memory allocation error: create_env_lst\n"));
	(*env_node)->key = ft_strndup(ms()->ms_env[i], \
	ft_strlen_c(ms()->ms_env[i], '='));
	(*env_node)->value = ft_strdup(ft_strchr(ms()->ms_env[i], '=') + 1);
	(*env_node)->invis = 0;
	(*env_node)->next = NULL;
}

void	create_env_lst(void)
{
	int		i;
	t_env	*env_node;
	t_env	*temp;

	i = 0;
	while (ms()->ms_env[i] != NULL)
	{
		env_node = NULL;
		new_env(&env_node, i);
		if (!ms()->env_lst)
			ms()->env_lst = env_node;
		else
		{
			temp = get_last_node(ms()->env_lst, get_offset(&dummy()->env, \
			&dummy()->env.next));
			temp->next = env_node;
		}
		if (!env_node->key || !env_node->value)
			return ((void)(clean_env_lst(), catch()->error_msg = \
			"Memory allocation error: create_env_lst\n"));
		i++;
	}
}

void	init(char **env)
{
	ms()->cmd = NULL;
	ms()->env_lst = NULL;
	ms()->exit_status = 0;
	ms()->here_sig = 0;
	ms()->exec = malloc(sizeof(t_exec));
	if (!ms()->exec)
	{
		ft_printf("Memory allocation error: init\n");
		exit(1);
	}
	ms()->exec->pwd = NULL;
	copy_env(env);
	create_env_lst();
	parse()->cmd_ll = NULL;
	parse()->arg_ll = NULL;
	catch()->error_msg = NULL;
}
