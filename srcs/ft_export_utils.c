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

	h = 0;
	*value = NULL;
	while (arg[h] && arg[h] != '=')
		h++;
	if (arg[h] == '=')
	{
		*key = ft_substr(arg, 0, h);
		if (!key)
			return ((void)(catch()->error_msg = "Substr failed"));
		*value = ft_strdup(arg + h + 1);
		if (!value)
			return (free(key), (void)(catch()->error_msg = "Strdup failed"));
	}
	else
		no_value(arg, key, value);
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
				if (!temp->value)
					return ((void)(catch()->error_msg = "Substr failed"));
			}
			temp->invis = 0;
			return ;
		}
		temp = temp->next;
	}
	if (catch()->error_msg == NULL)
		add_env_key(env, key, value);
}

void	add_env_key(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ((void)(catch()->error_msg = "Error adding new env key\n"));
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), (void)(catch()->error_msg
			= "Strdup failed"));
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), free(new_node),
				(void)(catch()->error_msg = "Substr failed"));
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
