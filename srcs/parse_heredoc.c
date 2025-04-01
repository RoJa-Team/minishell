/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:18:59 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/01 21:59:21 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	receive_content(char *del, int here)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
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

int	check_existing_heredoc(void)
{
	t_redir	*temp_redir;

	temp_redir = ((t_cmd *)get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, \
	&dummy()->cmd.next)))->fd_in;
	while (temp_redir != NULL)
	{
		if (temp_redir->type == HEREDOC)
			return (ft_atoi(temp_redir->file));
		temp_redir = temp_redir->next;
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	static int	fds[2];
	// int			save_stdin;

	fds[0] = check_existing_heredoc();
	if (fds[0] != 0)
		close(fds[0]);
	if (pipe(fds) == -1)
		deallocate("error creating pipe");
	debug("fd 0", fds[0]);
	debug("fd 1", fds[1]);
	receive_content(delimiter, fds[1]);
	// save_stdin = dup(STDIN_FILENO);
	// dup2(fds[0], STDIN_FILENO);
	// dup2(save_stdin, STDIN_FILENO);
	// close(save_stdin);
	close(fds[1]);
	return (fds[0]);
}