/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:59:42 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/09 20:16:43 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	update_env_lst(t_env *env, char *key, char *new_value)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(new_value);
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
