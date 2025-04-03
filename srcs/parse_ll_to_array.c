/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ll_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:15 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/01 18:27:18 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	token_to_array(t_cmd *cmd_ll, t_parse *arg_ll)
{
	int		i;
	t_cmd	dummy_cmd;
	t_parse	dummy_arg;
	t_cmd	*last_cmd;
	t_parse	*temp;

	last_cmd = get_last_node(cmd_ll, get_offset(&dummy_cmd, &dummy_cmd.next));
	last_cmd->arg = malloc(sizeof(char *) * (get_list_size(arg_ll, \
	get_offset(&dummy_arg, &dummy_arg.next)) + 1));
	if (!last_cmd->arg)
		deallocate("Error> ll_to_array");
	i = 0;
	while (arg_ll != NULL)
	{
		last_cmd->arg[i] = arg_ll->token;
		temp = arg_ll->next;
		free(arg_ll);
		arg_ll = temp;
		i++;
	}
	last_cmd->arg[i] = 0;
}

void	cmd_to_array(t_cmd *cmd_ll)
{
	int		i;
	t_cmd	dummy_cmd;
	t_cmd	*temp_cmd;

	ms()->cmd = malloc(sizeof(char *) * (get_list_size(cmd_ll, \
	get_offset(&dummy_cmd, &dummy_cmd.next)) + 1));
	if (!ms()->cmd)
		deallocate("Error> cmd_to_array");
	temp_cmd = cmd_ll;
	i = 0;
	while (temp_cmd != NULL)
	{
		ms()->cmd[i] = temp_cmd;
		i++;
		temp_cmd = temp_cmd->next;
	}
	ms()->cmd[i] = 0;
}
