/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:18:59 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/21 21:06:23 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_delimiter(char *str, int *i)
{
	int		len;
	int		quotes;
	char	*delimiter;

	len = 0;
	quotes = 0;
	while (str[*i + len])
	{
		check_quotes(str[*i + len], &quotes);
		if (quotes == 0 && check_metachar(str[*i + len]))
			break ;
		len++;
	}
	delimiter = malloc(sizeof(char) * len + 1);
	if (!delimiter)
		deallocate("Error> get_file");
	len = 0;
	while (str[*i])
	{
		check_quotes(str[*i], &quotes);
		if (quotes == 0 && check_metachar(str[*i]))
			break ;
		if ((str[*i] != '\'') && (str[*i] != '\"'))
		{
			delimiter[len] = str[*i];
			len++;
		}
		(*i)++;
	}
	delimiter[len] = '\0';
	return (delimiter);
}

int	handle_heredoc(char *delimiter)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		deallocate("error creating pipe");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	return (fds[1]);
}