/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:08:53 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 12:23:23 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	heredoc_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		else if (check_metachar(str[i]))
			break ;
		else
			i++;
	}
	return (0);
}

int	heredoc_del_final_len(char *str)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (str[i + 1] == '\"' || str[i + 1] == '\'') \
		&& quotes == 0)
			;
		else if (str[i] == '\"' || str[i] == '\'')
		{
			if ((quotes == 2 && str[i] == '\'') || \
			(quotes == 1 && str[i] == '\"'))
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

void	heredoc_del_final_str(char *str, char *final_del)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (str[i + 1] == '\"' || str[i + 1] == '\'') \
		&& quotes == 0)
			;
		else if (str[i] == '\"' || str[i] == '\'')
		{
			if ((quotes == 2 && str[i] == '\'') || \
			(quotes == 1 && str[i] == '\"'))
				final_del[len++] = str[i];
		}
		else
			final_del[len++] = str[i];
		i++;
	}
}

char	*remove_quotes_heredoc(char *str)
{
	char	*final_del;

	if (!str)
		return (NULL);
	final_del = ft_calloc(sizeof(char), heredoc_del_final_len(str) + 1);
	if (!final_del)
		return (free(str), catch()->error_msg = \
		"Memory allocation error: remove_quotes_heredoc\n", NULL);
	heredoc_del_final_str(str, final_del);
	free(str);
	return (final_del);
}
