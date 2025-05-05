/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:35:03 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/25 19:21:54 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**convert_lst_to_arr(t_env *lst)
{
	char	**arr;
	int		size;
	int		i;
	int		status;

	size = env_lst_size(lst);
	arr = malloc(sizeof(char *) * (size + 1));
	status = -1;
	if (!arr)
		return (catch()->error_msg = "Memory Allocation failed", NULL);
	i = 0;
	while (lst)
	{
		status = assign_value_to_array(&i, lst, arr);
		if (status == 0)
			return (free(arr), catch()->error_msg
				= "Error allocating memory", NULL);
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	assign_value_to_array(int *i, t_env *lst, char **arr)
{
	char	*temp;

	temp = NULL;
	if (lst->value)
	{
		temp = ft_strjoin(lst->key, "=");
		if (!temp)
			return (0);
		arr[*i] = ft_strjoin(temp, lst->value);
		if (!arr[*i])
			return (free(temp), (catch()->error_msg = "Strdup failed"), 0);
		free(temp);
	}
	else
		arr[*i] = ft_strdup(lst->key);
	if (!arr[*i])
	{
		while (*i-- > 0)
			free(arr[*i]);
		free(arr);
		return (0);
	}
	return (1);
}

int	env_lst_size(t_env *env_lst)
{
	int	size;

	size = 0;
	while (env_lst)
	{
		size++;
		env_lst = env_lst->next;
	}
	return (size);
}

char	*find_value(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	free_key_and_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}
