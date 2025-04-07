/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ll_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:15 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/07 22:07:49 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	token_to_array(void)
{
	int		i;
	t_cmd	*last_cmd;
	t_arg	*temp;

	last_cmd = get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, &dummy()->cmd.next));
	last_cmd->arg = malloc(sizeof(char *) * (get_list_size(parse()->arg_ll, \
	get_offset(&dummy()->arg, &dummy()->arg.next)) + 1));
	if (!last_cmd->arg)
		deallocate("Memory allocation error: token_to_array\n");
	i = 0;
	while (parse()->arg_ll != NULL)
	{
		last_cmd->arg[i] = parse()->arg_ll->word;
		temp = parse()->arg_ll->next;
		free(parse()->arg_ll);
		parse()->arg_ll = temp;
		i++;
	}
	last_cmd->arg[i] = NULL;
	parse()->arg_ll = NULL;
}

void	cmd_to_array(void)
{
	int		i;
	t_cmd	*temp_cmd;

	if (!parse()->cmd_ll)
		return ;
	ms()->cmd = malloc(sizeof(t_cmd *) * (get_list_size(parse()->cmd_ll, \
	get_offset(&dummy()->cmd, &dummy()->cmd.next)) + 1));
	if (!ms()->cmd)
		deallocate("Memory allocation error: cmd_to_array\n");
	temp_cmd = parse()->cmd_ll;
	i = 0;
	while (temp_cmd != NULL)
	{
		ms()->cmd[i] = temp_cmd;
		i++;
		temp_cmd = temp_cmd->next;
	}
	ms()->cmd[i] = NULL;
	parse()->cmd_ll = NULL;
}
