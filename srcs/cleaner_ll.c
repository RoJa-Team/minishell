/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:12:01 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/07 15:55:08 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clean_arg_ll(void)
{
	t_arg	*arg_temp;

	if (parse()->arg_ll)
	{
		while (parse()->arg_ll != NULL)
		{
			arg_temp = parse()->arg_ll;
			parse()->arg_ll = arg_temp->next;
			free(arg_temp->word);
			free(arg_temp);
		}
	}
}

void	clean_redir_ll(t_cmd *cmd_temp)
{
	t_redir	*redir_temp;

	while (cmd_temp->redir != NULL)
	{
		redir_temp = cmd_temp->redir;
		cmd_temp->redir = redir_temp->next;
		free(redir_temp->file);
		free(redir_temp);
	}
}

void	clean_parse(void)
{
	int		i;
	t_cmd	*cmd_temp;

	clean_arg_ll();
	if (parse()->cmd_ll)
	{
		while (parse()->cmd_ll != NULL)
		{
			cmd_temp = parse()->cmd_ll;
			parse()->cmd_ll = cmd_temp->next;
			clean_redir_ll(cmd_temp);
			if (cmd_temp->arg)
			{
				i = 0;
				while (cmd_temp->arg[i])
				{
					free(cmd_temp->arg[i]);
					i++;
				}
				free(cmd_temp->arg);
			}
			free(cmd_temp);
		}
	}
}
