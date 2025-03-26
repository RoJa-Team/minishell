/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:57 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/26 20:36:21 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	expansion_len(t_ms *ms, char *str, int *i)
{
	int	len;

	(*i)++;
	len = 0;
	if (str[*i] == '?')
		len++;
	else if (ft_isdigit(str[*i]))
		deallocate("Error> invalid identifier");
	else
		while (str[*i + len] && !check_metachar(str[*i + len]) && \
		str[*i + len] != '\'' && str[*i + len] != '\"')
			len++;
	*i = *i + len;
	return (ft_strlen(find_env_value(ms, str, *i - len, len)));
}

int	exp_len(t_ms *ms, char *str)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	check_quotes(str[i], &quotes);
	while (str[i])
	{
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			len = len + expansion_len(ms, str, &i);
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
				len++;
			i++;
		}
		check_quotes(str[i], &quotes);
	}
	return (len);
}

char	*expansion_value(t_ms *ms, char *str, int *i)
{
	int	len;

	(*i)++;
	len = 0;
	while (str[*i + len] && !check_metachar(str[*i + len]) && \
	str[*i + len] != '\'' && str[*i + len] != '\"')
		len++;
	*i = *i + len;
	return (find_env_value(ms, str, *i - len, len));
}

char	*final_str(t_ms *ms, char *str, char *arg, int i)
{
	int		len;
	int		quotes;
	char	*val;

	len = 0;
	quotes = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
		{
			val = expansion_value(ms, str, &i);
			ft_strlcat(&arg[len], val, ft_strlen(arg) + ft_strlen(val) + 1);
			len = len + ft_strlen(val);
		}
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
				arg[len++] = str[i];
			i++;
		}
	}
	arg[len] = '\0';
	return (arg);
}

char	*expand_str(t_ms *ms, char *str)
{
	char	*arg;

	if (!str)
		return (NULL);
	arg = ft_calloc(sizeof(char), exp_len(ms, str) + 1);
	if (!arg)
		deallocate ("Error> expand_token");
	return (final_str(ms, str, arg, 0));
}
