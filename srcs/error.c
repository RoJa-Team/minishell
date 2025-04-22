/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:36:25 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/17 19:06:57 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
}

// void	clean_parse(t_ms *ms)
// {
// 	// t_parse	*temp;

// 	// while (ms->parse != NULL)
// 	// {
// 	// 	temp = ms->parse;
// 	// 	ms->parse = temp->next;
// 	// 	free(temp->token);
// 	// }

// 	t_cmd	*ll_cmd;
// 	t_parse	*ll_token;

// 	ll_cmd = ms->cmds;
// 	while (ms->cmds != NULL)
// 	{
// 		ll_cmd = ms->cmds;
// 		while (ms->cmds->token != NULL)
// 		{
// 			ll_token = ms->cmds->token;
// 			ms->cmds->token = ll_token->next;
// 			free(ll_token);
// 		}
// 		ms->cmds = ll_cmd->next;
// 	}
// }

void	bad_input(char *message, int error)
{
	ms()->exit_status = error;
	ft_printf("%s\n", message);
}

void	deallocate(char *message)
{
	clean_structs();
	exit(ft_printf(message));
}
