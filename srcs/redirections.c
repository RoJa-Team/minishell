/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:05:28 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/01 21:55:05 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	handle_redirections(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->fd_in;
	if (r)
		handle_input_r(r);
	r = cmd->fd_out;
	if (r)
		handle_output_r(r);
}

void	handle_input_r(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type == 1)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				deallocate("no such file or directory");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == 2)
			execute_heredoc(r);
		r = r->next;
	}
}

void	handle_output_r(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type == 1)
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

void	execute_heredoc(t_redir *r)
{
	int	fd;

	fd = ft_atoi(r->file);
	if (fd < 0)
		deallocate("heredoc error\n");
	dup2(fd, STDIN_FILENO);
	close(fd);
}
