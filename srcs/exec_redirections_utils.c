/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:22:16 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/09 21:48:05 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ambiguous_redirect(t_cmd *cmd, int *res)
{
	cmd->cmd_status = 1;
	*res = 1;
	cmd->error_msg = ft_strdup("ambiguous redirect\n");
	if (!cmd->error_msg)
		return (catch()->error_msg = "ft_strdup failed", (void) NULL);
}

int	check_redir_input(t_redir *redir)
{
	t_redir	*temp_redir;

	if (redir == NULL)
		return (0);
	temp_redir = redir;
	while (temp_redir != NULL)
	{
		if (temp_redir->type == INPUT)
			return (1);
		temp_redir = temp_redir->next;
	}
	return (0);
}

int	check_redir_output(t_redir *redir)
{
	t_redir	*temp_redir;

	if (redir == NULL)
		return (0);
	temp_redir = redir;
	while (temp_redir != NULL)
	{
		if (temp_redir->type == OUTPUT)
			return (1);
		temp_redir = temp_redir->next;
	}
	return (0);
}
