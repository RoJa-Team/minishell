/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:18:59 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/01 19:23:47 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	receive_content(char *delimiter, int here)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			write(here, "\n", 1); //TODO shorten this
			break ;
		}
		write(here, line, ft_strlen(line));
		write(here, "\n", 1); //because of this
		free(line);
	}
}

int	handle_heredoc(char *delimiter)
{
	int		fds[2];
	int		save_stdin;

	//if (get_last_node(((t_cmd *)get_last_node(ms()->cmd, get_offset(&ms()->dummy.cmd, &ms()->dummy.cmd.next)))->fd_in, get_offset(&ms()->dummy.redir, &ms()->dummy.redir.next)));

	if (pipe(fds) == -1)
		deallocate("error creating pipe");
	receive_content(delimiter, fds[1]);
	save_stdin = dup(STDIN_FILENO);
	dup2(fds[0], STDIN_FILENO);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(fds[1]);
	return (fds[0]);
}