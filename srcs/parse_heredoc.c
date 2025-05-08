/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:18:59 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/07 16:04:43 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	receive_content(char *del, int here, int quote)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strncmp(line, del, ft_strlen(del) + 1) == 0 || \
		ms()->here_sig)
			return (free(line), free(del));
		if (quote == 0)
		{
			expanded = expand_here(line);
			write(here, expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
		{
			write(here, line, ft_strlen(line));
			free(line);
		}
		write(here, "\n", 1);
	}
}

int	check_existing_heredoc(void)
{
	t_redir	*temp_redir;

	temp_redir = ((t_cmd *)get_last_node(parse()->cmd_ll, \
	get_offset(&dummy()->cmd, &dummy()->cmd.next)))->redir;
	while (temp_redir != NULL)
	{
		if (temp_redir->type == INPUT && temp_redir->operator == HEREDOC)
			return (ft_atoi(temp_redir->file));
		temp_redir = temp_redir->next;
	}
	return (0);
}

int	handle_heredoc(int quote, char *delimiter)
{
	static int	fds[2];

	if (catch()->error_msg)
		return (0);
	fds[0] = check_existing_heredoc();
	if (fds[0] != 0)
		close(fds[0]);
	if (pipe(fds) == -1)
		return (catch()->error_msg = "Pipe creation error: handle_heredoc\n"\
		, 0);
	setup_heredoc();
	receive_content(delimiter, fds[1], quote);
	setup_parse();
	close(fds[1]);
	if (ms()->here_sig)
	{
		close(fds[0]);
		return (0);
	}
	return (fds[0]);
}
