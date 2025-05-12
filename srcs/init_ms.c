/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:49:48 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 11:07:13 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	copy_env(char **env)
{
	int	i;

	i = 0;
	if (catch()->error_msg != NULL)
		return ;
	while (env[i])
		i++;
	ms()->ms_env = ft_calloc(sizeof(char *), (i + 1));
	if (!ms()->ms_env)
		return ((void)(catch()->error_msg = \
		"Memory allocation error: copy_env\n"));
	i = 0;
	while (env[i])
	{
		ms()->ms_env[i] = ft_strdup(env[i]);
		if (!ms()->ms_env[i])
			return ((void)(catch()->error_msg = \
			"Memory allocation error: copy_env\n"));
		i++;
	}
	ms()->ms_env[i] = NULL;
}

t_env	*new_env(int i)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (catch()->error_msg = \
		"Memory allocation error: new_env\n", NULL);
	env_node->invis = 0;
	env_node->next = NULL;
	env_node->key = ft_strndup(ms()->ms_env[i], \
	ft_strlen_c(ms()->ms_env[i], '='));
	if (!env_node->key)
		return (free(env_node), catch()->error_msg = \
		"Memory allocation error: new_env\n", NULL);
	env_node->value = ft_strdup(ft_strchr(ms()->ms_env[i], '=') + 1);
	if (!env_node->value)
		return (free(env_node->key), free(env_node), catch()->error_msg = \
		"Memory allocation error: new_env\n", NULL);
	return (env_node);
}

void	create_env_lst(void)
{
	int		i;
	t_env	*env_node;
	t_env	*temp;

	if (catch()->error_msg != NULL)
		return ;
	i = 0;
	while (ms()->ms_env[i] != NULL)
	{
		env_node = new_env(i);
		if (catch()->error_msg != NULL)
			return ;
		if (!ms()->env_lst)
			ms()->env_lst = env_node;
		else
		{
			temp = get_last_node(ms()->env_lst, get_offset(&dummy()->env, \
			&dummy()->env.next));
			temp->next = env_node;
		}
		i++;
	}
}

void	init(char **env)
{
	catch()->error_msg = NULL;
	parse()->cmd_ll = NULL;
	parse()->arg_ll = NULL;
	ms()->cmd = NULL;
	ms()->env_lst = NULL;
	ms()->exit_status = 0;
	ms()->here_sig = 0;
	ms()->exec = malloc(sizeof(t_exec));
	if (!ms()->exec)
		return ((void)(catch()->error_msg = \
		"Memory allocation error: init\n"));
	(ms()->exec->pwd) = getcwd(NULL, 0);
	if (!ms()->exec->pwd)
		return ((void)(catch()->error_msg = \
		"Memory allocation error or directory couldn't be determined: init\n"));
	copy_env(env);
	if (catch()->error_msg != NULL)
		return ;
	create_env_lst();
	if (catch()->error_msg != NULL)
		return ;
}
