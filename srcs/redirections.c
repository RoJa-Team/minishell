/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:05:28 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/18 20:53:09 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	handle_redirections(t_cmd *cmd)
{
	t_redir	*r;
	
	r = cmd->fd_in;
	handle_input_r(r);
	r = cmd->fd_out;
	handle_output_r(r);
}

void	handle_input_r(t_redir *r)
{
	int	fd;

	while (r)
	{
		if(r->type == 1)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				deallocate("no such file or directory");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == 2)
			handle_heredoc(r->file);
		r = r->next;
	}
}

void	handle_output_r(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type = 1)
		{
			fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				deallocate("truncating error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == 2)
		{
			fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				deallocate("appending error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		r = r->next;
	}
}

void	handle_heredoc(char *delimiter)
{
	char	*line;
	int	fds[2];

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
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}
