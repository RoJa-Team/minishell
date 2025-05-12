/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:18:59 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 13:58:29 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	receive_content(char *del, int here, int quote)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strncmp(line, del, ft_strlen(del) + 1) == 0 || \
		ms()->here_sig)
			return (free(line), free(del));
		if (quote == 0)
		{
			line = expand_here(line);
			if (line == NULL && catch()->error_msg != NULL)
				return (free(del));
			if (line)
			{
				ft_putendl_fd(line, here);
				free(line);
			}
		}
		else
		{
			ft_putendl_fd(line, here);
			free(line);
		}
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
		{
			if (!temp_redir->file)
				break ;
			return (ft_atoi(temp_redir->file[0]));
		}
		temp_redir = temp_redir->next;
	}
	return (0);
}

char	**alloc_heredoc_file(int fd)
{
	char	**file;

	file = ft_calloc(sizeof(char *), 2);
	if (!file)
		return (close(fd), catch()->error_msg = \
		"Memory allocation error: alloc_heredoc_file\n", NULL);
	if (ms()->here_sig)
	{
		close(fd);
		file[0] = ft_itoa(0);
		if (!file[0])
			return (free(file), catch()->error_msg = \
			"Memory allocation error: ft_itoa - alloc_heredoc_file\n", NULL);
		return (file);
	}
	file[0] = ft_itoa(fd);
	if (!file[0])
		return (free(file), close(fd), catch()->error_msg = \
		"Memory allocation error: ft_itoa - alloc_heredoc_file\n", NULL);
	return (file);
}

char	**handle_heredoc(int quote, char *delimiter)
{
	static int	fds[2];

	if (catch()->error_msg != NULL)
		return (NULL);
	fds[0] = check_existing_heredoc();
	if (fds[0] != 0)
		close(fds[0]);
	if (pipe(fds) == -1)
		return (free(delimiter), catch()->error_msg = \
		"Pipe creation error: handle_heredoc\n", NULL);
	setup_heredoc();
	if (catch()->error_msg != NULL)
		return (free(delimiter), close(fds[0]), close(fds[1]), NULL);
	receive_content(delimiter, fds[1], quote);
	if (catch()->error_msg != NULL)
		return (close(fds[0]), close(fds[1]), NULL);
	setup_parse();
	if (catch()->error_msg != NULL)
		return (close(fds[0]), close(fds[1]), NULL);
	close(fds[1]);
	return (alloc_heredoc_file(fds[0]));
}
