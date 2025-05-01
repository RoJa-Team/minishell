/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:51:45 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/01 20:54:44 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**remove_quotes(char **split_arg, int quotes)
{
	int		i;
	int		len;
	int		n_strs;
	char	**str_arr;

	if (split_arg == NULL)
		return (NULL);
	n_strs = 0;
	while (split_arg[n_strs] != NULL)
		n_strs++;
	str_arr = ft_calloc(sizeof(char *), n_strs + 1);
	if (!str_arr)
		return (free_array(split_arg), catch()->error_msg = \
		"Memory allocation error: remove_quotes\n", NULL);
	n_strs = 0;
	while (split_arg[n_strs] != NULL)
	{
		i = 0;
		len = 0;
		while (split_arg[n_strs][i] != '\0')
		{
			check_quotes(split_arg[n_strs][i], &quotes);
			if (split_arg[n_strs][i] == '\"' || split_arg[n_strs][i] == '\'')
			{
				if ((quotes == 2 && split_arg[n_strs][i] == '\'') || \
				(quotes == 1 && split_arg[n_strs][i] == '\"'))
					len++;
			}
			else
				len++;
			i++;
		}
		str_arr[n_strs] = ft_calloc(sizeof(char), len + 1);
		if (!str_arr[n_strs])
			return (free_array(split_arg), free_array(str_arr), \
			catch()->error_msg = "Memory allocation error: remove_quotes\n", \
			NULL);
		i = 0;
		len = 0;
		while (split_arg[n_strs][i] != '\0')
		{
			check_quotes(split_arg[n_strs][i], &quotes);
			if (split_arg[n_strs][i] == '\"' || split_arg[n_strs][i] == '\'')
			{
				if ((quotes == 2 && split_arg[n_strs][i] == '\'') || \
				(quotes == 1 && split_arg[n_strs][i] == '\"'))
					str_arr[n_strs][len++] = split_arg[n_strs][i];
			}
			else
				str_arr[n_strs][len++] = split_arg[n_strs][i];
			i++;
		}
		n_strs++;
	}
	free_array(split_arg);
	return (str_arr);
}