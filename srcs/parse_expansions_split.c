/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:33:24 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/01 21:09:42 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**allocate_strs(char **split_arg, char *arg, int n_str, int quotes)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] != '\0')
	{
		len = 0;
		while (arg[i] != '\0')
		{
			check_quotes(arg[i], &quotes);
			if (arg[i] == ' ' && quotes == 0)
				break ;
			len++;
			i++;
		}
		split_arg[n_str] = ft_calloc(sizeof(char), len + 1);
		if (!split_arg[n_str])
			return (free_array(split_arg), catch()->error_msg = \
			"Memory allocation error: allocate_strs\n", NULL);
		n_str++;
		if (arg[i] != '\0')
			i++;
	}
	split_arg[n_str] = NULL;
	return (split_arg);
}

char	**allocate_split(char *arg)
{
	int		i;
	int		n_str;
	int		quotes;
	char	**split_arg;

	i = 0;
	n_str = 1;
	quotes = 0;
	while (arg[i] != '\0')
	{
		check_quotes(arg[i], &quotes);
		if (arg[i] == ' ' && quotes == 0)
			n_str++;
		i++;
	}
	split_arg = ft_calloc(sizeof(char *), n_str + 1);
	if (!split_arg)
		return (catch()->error_msg = \
		"Memory allocation error: allocate_split\n", NULL);
	split_arg[n_str] = NULL;
	return (split_arg);
}

char	**split_expansion(char *arg, int i, int n_str, int quotes)
{
	int		j;
	char	**split_arg;

	split_arg = allocate_split(arg);
	if (!split_arg)
		return (NULL);
	split_arg = allocate_strs(split_arg, arg, 0, 0);
	if (!split_arg)
		return (NULL);
	j = 0;
	while (arg[i] != '\0')
	{
		check_quotes(arg[i], &quotes);
		if (!(arg[i] == ' ' && quotes == 0))
			split_arg[n_str][j++] = arg[i];
		else
		{
			j = 0;
			n_str++;
		}
		i++;
	}
	free(arg);
	return (split_arg);
}
