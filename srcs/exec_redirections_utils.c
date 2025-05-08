/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:22:16 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/07 19:22:18 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
