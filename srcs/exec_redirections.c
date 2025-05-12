/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:05:28 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/12 12:40:38 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	int		res;
	t_redir	*r;

	res = 0;
	r = cmd->redir;
	while (r && cmd->error_msg == NULL)
	{
		if (!r->file || (r->file && r->file[1] != NULL))
		{
			ambiguous_redirect(cmd, &res);
			break ;
		}
		if (r->type == INPUT)
			handle_input_r(cmd, r, &res);
		else
			handle_output_r(cmd, r, &res);
		r = r->next;
	}
	if (cmd->error_msg != NULL)
	{
		ft_putstr_fd(cmd->error_msg, 2);
		free(cmd->error_msg);
	}
	return (res);
}

void	handle_input_r(t_cmd *cmd, t_redir *r, int *res)
{
	int			fd;
	struct stat	st;

	fd = 0;
	ft_memset(&st, 0, sizeof(struct stat));
	if (r->operator == IN)
	{
		fd = open(r->file[0], O_RDONLY);
		stat(r->file[0], &st);
		if ((fd < 0) || (!S_ISREG(st.st_mode)))
			check_access(cmd, r, res, st);
		else if (cmd->arg)
			dup2(fd, STDIN_FILENO);
		if (fd != -1)
			close(fd);
	}
	else if (r->operator == HEREDOC)
		execute_heredoc(cmd, r, res, st);
}

void	handle_output_r(t_cmd *cmd, t_redir *r, int *res)
{
	int			fd;
	struct stat	st;

	fd = 0;
	ft_memset(&st, 0, sizeof(struct stat));
	if (r->operator == OUT)
		fd = open(r->file[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->operator == APPEND)
		fd = open(r->file[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	stat(r->file[0], &st);
	if ((fd < 0) || (!S_ISREG(st.st_mode)))
		check_access(cmd, r, res, st);
	else if (cmd->arg)
		dup2(fd, STDOUT_FILENO);
	if (fd != -1)
		close(fd);
}

void	execute_heredoc(t_cmd *cmd, t_redir *r, int *res, struct stat st)
{
	int	fd;

	fd = ft_atoi(r->file[0]);
	if (fd < 0)
		check_access(cmd, r, res, st);
	else if (cmd->arg)
		dup2(fd, STDIN_FILENO);
	close(fd);
}

void	check_access(t_cmd *cmd, t_redir *r, int *res, struct stat st)
{
	char	*filename;

	filename = r->file[0];
	if (access(filename, F_OK) == -1 && cmd->error_msg == NULL)
		cmd->error_msg = ft_strjoin(filename, ": No such file or directory\n");
	else if ((access(filename, R_OK) == -1 || access(filename, W_OK) == -1)
		&& cmd->error_msg == NULL)
		cmd->error_msg = ft_strjoin(filename, ": Permission denied\n");
	else if (!S_ISREG(st.st_mode) && cmd->error_msg == NULL)
		cmd->error_msg = ft_strjoin(filename, ": Is a directory\n");
	if (cmd->error_msg == NULL)
		catch()->error_msg = "Strjoin failed";
	cmd->cmd_status = 1;
	*res = 1;
}
