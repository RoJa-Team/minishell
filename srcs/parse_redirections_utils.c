/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:08:53 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/23 19:35:22 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	heredoc_quote(char *str)
{
	int		i;

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

int	file_len(char *str)
{
	int	i;
	int	wq;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			wq = within_quotes(&str[i]);
			i = i + wq;
			len = len + wq - 2;
		}
		else if (check_metachar(str[i]))
			break ;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*get_del(char *str, int *i, int len, int quotes)
{
	int		j;
	char	*del;

	len = file_len(&str[*i]);
	del = malloc(sizeof(char) * len + 1);
	if (!del)
		deallocate("Memory allocation error: get_del\n");
	j = 0;
	while (j < len && str[*i])
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			check_quotes(str[*i], &quotes);
			if ((quotes == 2 && str[*i] == '\'') || (quotes == 1 && \
				str[*i] == '\"'))
				del[j++] = str[*i];
		}
		else
			del[j++] = str[*i];
		(*i)++;
	}
	del[j] = '\0';
	while (str[*i] && !check_metachar(str[*i]))
		(*i)++;
	return (del);
}

char	*get_file(char *str, int *i, int len, int quotes)
{
	int		j;
	char	*file;

	len = file_len(&str[*i]);
	file = malloc(sizeof(char) * len + 1);
	if (!file)
		deallocate("Memory allocation error: get_file\n");
	j = 0;
	while (j < len && str[*i])
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			check_quotes(str[*i], &quotes);
			if ((quotes == 2 && str[*i] == '\'') || (quotes == 1 && \
				str[*i] == '\"'))
				file[j++] = str[*i];
		}
		else
			file[j++] = str[*i];
		(*i)++;
	}
	file[j] = '\0';
	return (file);
}
