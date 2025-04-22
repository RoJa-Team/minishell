/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:57 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/22 19:39:18 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	final_len(char *str, int len, int quotes, int wq)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			len = len + ft_strlen(expansion_value(str, &i));
		else
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				wq = within_quotes(&str[i]);
				i = i + wq;
				len = len + wq - 2;
			}
			else
			{
				len++;
				i++;
			}
		}
	}
	return (len);
}

void	copy_exp_value(char *str, char *arg, int *i, int *j)
{
	char	*val;

	val = expansion_value(str, i);
	ft_strlcat(&arg[*j], val, ft_strlen(arg) + ft_strlen(val) + 1);
	*j = *j + ft_strlen(val);
}

char	*final_str(char *str, char *arg, int i, int quotes)
{
	int		j;

	j = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			copy_exp_value(str, arg, &i, &j);
		else
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				if ((quotes == 2 && str[i] == '\'') || (quotes == 1 && \
					str[i] == '\"'))
					arg[j++] = str[i];
			}
			else
				arg[j++] = str[i];
			i++;
		}
	}
	return (arg);
}

char	*expand_str(char *str)
{
	int		len;
	char	*arg;

	if (!str)
		return (NULL);
	len = final_len(str, 0, 0, 0);
	if (len == 0)
		return (free(str), NULL);
	arg = ft_calloc(sizeof(char), len + 1);
	if (!arg)
		deallocate ("Memory allocation error: expand_str\n");
	arg = final_str(str, arg, 0, 0);
	free(str);
	return (arg);
}
