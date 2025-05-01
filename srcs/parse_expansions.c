/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:57 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/01 20:52:01 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	final_len(char *str, int len, int quotes)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0) && \
		!check_metachar(str[i + 1]))
			len = len + ft_strlen(expansion_value(str, &i, 1));
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	copy_exp_value(char *str, char *arg, int *i, int *j)
{
	char	*val;

	val = expansion_value(str, i, 0);
	if (val != NULL)
	{
		ft_strlcat(&arg[*j], val, ft_strlen(arg) + ft_strlen(val) + 1);
		*j = *j + ft_strlen(val);
	}
}

void	final_str(char *str, char *arg, int i, int quotes)
{
	int	j;

	j = 0;
	while (str[i] && catch()->error_msg == NULL)
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0) \
		&& !check_metachar(str[i + 1]))
			copy_exp_value(str, arg, &i, &j);
		else
		{
			arg[j++] = str[i];
			i++;
		}
	}
}

char	**expand_str(char *str)
{
	int		len;
	char	*arg;
	char	**str_arr;

	if (!str || catch()->error_msg != NULL)
		return (NULL);
	len = final_len(str, 0, 0);
	if (len == 0 || catch()->error_msg != NULL)
		return (free(str), NULL);
	arg = ft_calloc(sizeof(char), len + 1);
	if (!arg)
		return (free(str), catch()->error_msg = \
		"Memory allocation error: expand_str\n", NULL);
	final_str(str, arg, 0, 0);
	str_arr = NULL;
	if (arg)
		str_arr = remove_quotes(split_expansion(arg, 0), 0);
	return (free(str), str_arr);
}
