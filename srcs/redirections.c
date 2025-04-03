/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:05:28 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/03 19:35:12 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int	res;

	res = 0;
	r = cmd->fd_in;
	if (r)
		handle_input_r(r, &res);
	r = cmd->fd_out;
	if (r)
		handle_output_r(r, &res);
	return (res);
}

void	handle_input_r(t_redir *r, int *res)
{
	int	fd;

	(void)res;
	while (r)
	{
		if (r->type == 1)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				check_access(r, res);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == 2)
			execute_heredoc(r, res);
		r = r->next;
	}
}

void	handle_output_r(t_redir *r, int *res)
{
	int	fd;

	(void)res;
	while (r)
	{
		if (r->type == 1)
		{
			fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				check_access(r, res);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == 2)
		{
			fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				check_access(r, res);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		r = r->next;
	}
}

void	execute_heredoc(t_redir *r, int *res)
{
	int	fd;

	(void)res;
	fd = ft_atoi(r->file);
	if (fd < 0)
		check_access(r, res);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	check_access(t_redir *r, int *res)
{
	const char	*filename;

	filename = r->file;
	if (access(filename, F_OK) == -1)
		ft_printf("%s: No such file or directory\n", filename);
	else if (access(filename, R_OK) == -1 || access(filename, W_OK) == -1)
		ft_printf("%s: Permission denied\n", filename);
	ms()->exit_status = 1;
	*res = 1;
}
