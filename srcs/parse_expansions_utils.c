/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:35:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/26 20:36:33 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*find_env_value(t_ms *ms, char *str, int i, int key_len)
{
	t_env	*temp;

	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (ft_strlen_c(&str[i], str[i + key_len]) == ft_strlen(temp->key) && \
		!strncmp(&str[i], temp->key, key_len))
			break ;
		temp = temp->next;
	}
	if (temp)
		return (temp->value);
	return ("");
}
