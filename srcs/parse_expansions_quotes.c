/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:51:45 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 12:10:47 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	final_str_len(char *split_arg)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (split_arg[i] != '\0')
	{
		check_quotes(split_arg[i], &quotes);
		if (split_arg[i] == '\"' || split_arg[i] == '\'')
		{
			if ((quotes == 2 && split_arg[i] == '\'') || \
			(quotes == 1 && split_arg[i] == '\"'))
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

void	no_quotes_str(char *str_arr, char *split_arg)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (split_arg[i] != '\0')
	{
		check_quotes(split_arg[i], &quotes);
		if (split_arg[i] == '\"' || split_arg[i] == '\'')
		{
			if ((quotes == 2 && split_arg[i] == '\'') || \
			(quotes == 1 && split_arg[i] == '\"'))
				str_arr[len++] = split_arg[i];
		}
		else
			str_arr[len++] = split_arg[i];
		i++;
	}
}

char	**remove_quotes(char **split_arg, int n_strs)
{
	char	**str_arr;

	while (split_arg[n_strs] != NULL)
		n_strs++;
	str_arr = ft_calloc(sizeof(char *), n_strs + 1);
	if (!str_arr)
		return (free_array(split_arg), catch()->error_msg = \
		"Memory allocation error: remove_quotes\n", NULL);
	n_strs = 0;
	while (split_arg[n_strs] != NULL)
	{
		str_arr[n_strs] = ft_calloc(sizeof(char), \
		final_str_len(split_arg[n_strs]) + 1);
		if (!str_arr[n_strs])
			return (free_array(split_arg), free_array(str_arr), \
			catch()->error_msg = "Memory allocation error: remove_quotes\n", \
			NULL);
		no_quotes_str(str_arr[n_strs], split_arg[n_strs]);
		n_strs++;
	}
	free_array(split_arg);
	return (str_arr);
}
