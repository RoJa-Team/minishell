/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:59:42 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/25 19:21:51 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	update_env_lst(t_env *env, char *key, char *new_value)
{
	t_env	*temp;

	temp = env;
	if (!env)
		return ;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(new_value);
			if (!temp->value)
				return ((void)(catch()->error_msg = "Strdup failed"));
			return ;
		}
		temp = temp->next;
	}
}

void	update_ms_env(void)
{
	int		count;
	t_env	*temp1;

	count = 0;
	temp1 = ms()->env_lst;
	free_args(ms()->ms_env);
	while (temp1 != NULL)
	{
		count++;
		temp1 = temp1->next;
	}
	ms()->ms_env = malloc(sizeof(char *) * (count + 1));
	if (!ms()->ms_env)
		return ((void)(catch()->error_msg = "malloc failed"));
	if (catch()->error_msg == NULL)
		assign_to_ms_env();
}

void	free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	arg_count(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	no_value(char *arg, char **key, char **value)
{
	char	*copy;

	*key = ft_strdup(arg);
	if (!key)
		return ((void)(catch()->error_msg = "Strdup failed"));
	copy = find_value(ms()->env_lst, *key);
	if (copy)
	{
		*value = ft_strdup(copy);
		if (!value)
			return (free(key), (void)(catch()->error_msg
				= "strdup failed"));
	}
}
