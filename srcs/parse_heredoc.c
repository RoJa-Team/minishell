/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:18:59 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/26 21:00:37 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_heredoc(char *delimiter)
{
	int		fds[2];
	int		save_stdin;
	char	*line;

	save_stdin = dup(STDIN_FILENO);
	if (pipe(fds) == -1)
		deallocate("error creating pipe");
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			write(fds[1], "\n", 1); //TODO shorten this
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1); //because of this
		free(line);
	}
	dup2(fds[0], STDIN_FILENO);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(fds[1]);
	return (fds[0]);
}
