/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:22:42 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/01 18:36:17 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	get_key_and_value(char *arg, char **key, char **value)
{
	int		h;
	char	*copy;

	h = 0;
	*value = NULL;
	while (arg[h] && arg[h] != '=')
		h++;
	if (arg[h] == '=')
	{
		*key = ft_substr(arg, 0, h);
		*value = ft_strdup(arg + h + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		copy = find_value(ms()->env_lst, *key);
		if (copy)
			*value = ft_strdup(copy);
	}
}

int	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (0);
		i++;
	}
	return (1);
}

void	update_or_add_env_key(t_env **env, char *key, char *value)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (value)
			{
				if (temp->value)
					free(temp->value);
				temp->value = ft_strdup(value);
			}
			temp->invis = 0;
			return ;
		}
		temp = temp->next;
	}
	add_env_key(env, key, value);
}

void	add_env_key(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		deallocate("Error adding new env key\n");
	new_node->key = ft_strdup(key);
	if (value)
	{
		new_node->value = ft_strdup(value);
		new_node->invis = 0;
	}
	else
	{
		new_node->value = NULL;
		new_node->invis = 1;
	}
	new_node->next = *env;
	*env = new_node;
}

void	swap_str(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
