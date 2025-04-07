/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:57 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/07 21:50:21 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	expansion_len(char *str, int *i)
{
	int	len;

	(*i)++;
	len = 0;
	if (str[*i] == '?')
		len++;
	else if (ft_isdigit(str[*i]))
		len++;
	else
		while (str[*i + len] && (ft_isalnum(str[*i + len]) || str[*i + len] == '_'))
			len++;
	*i = *i + len;
	return (ft_strlen(find_env_value(str, *i - len, len)));
}

char	*expansion_value(char *str, int *i)
{
	int	len;

	(*i)++;
	len = 0;
	if (str[*i] == '?')
		len++;
	else if (ft_isdigit(str[*i]))
		len++;
	else
		while (str[*i + len] && (ft_isalnum(str[*i + len]) || str[*i + len] == '_'))
			len++;
	*i = *i + len;
	return (find_env_value(str, *i - len, len));
}

char	*final_str(char *str, char *arg, int i)
{
	int		j;
	int		quotes;
	char	*val;

	j = 0;
	quotes = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
		{
			val = expansion_value(str, &i);
			ft_strlcat(&arg[j], val, ft_strlen(arg) + ft_strlen(val) + 1);
			j = j + ft_strlen(val);
		}
		else
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				if ((quotes == 2 && str[i] == '\'') || (quotes == 1 && str[i] == '\"'))
					arg[j++] = str[i];
			}
			else
				arg[j++] = str[i];
			i++;
		}
	}
	arg[j] = '\0';
	return (arg);
}

int	final_len(char *str)
{
	int	i;
	int	wq;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	wq = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			len = len + expansion_len(str, &i);
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

char	*expand_str(char *str)
{
	char	*arg;

	if (!str)
		return (NULL);
	arg = ft_calloc(sizeof(char), final_len(str) + 1);
	if (!arg)
		deallocate ("Error> expand_token");
	arg = final_str(str, arg, 0);
	free(str);
	return (arg);
}
