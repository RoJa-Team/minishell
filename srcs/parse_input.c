/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/13 22:57:15 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	pipe_counter(char *str)
{
	int	pipes;
	int	quote;

	pipes = 0;
	quote = 0;
	while(*str)
	{ 
		if (*str == '"' && quote == 1)
			quote = 0;
		else if (*str == '"')
			quote = 1;
		if (*str == '|' && quote == 0)
			pipes++;
		str++;
	}
	if (quote == 1)
		deallocate("Error> invalid number of quotes.\n");
	return (pipes);
}

// void	quote_validator(char *str)
// {
// 	int	quote;

// 	quote = 0;
// 	while(*str)
// 	{
// 		if (*str == '"' && quote == 1)
// 			quote = 0;
// 		else if (*str == '"')
// 			quote = 1;
// 		str++;
// 	}
// 	if (quote == 1)
// 		deallocate("Error> invalid number of quotes.\n");
// }

void	redirections(t_ms *ms, char *str)
{
	while (*str)
	{
		if (*str == '>' && *(str + 1) == '>')
			;
		else if (*str == '<' && *(str + 1) == '<')
			;
		else if (*str == '>')
			;
		else if (*str == '<')
			;
		str++;
	}
}

void	parse_pipes(t_ms *ms, char *str, int pipes)
{
	int		i;
	char	**cmds;

	cmds = ft_split(str, '|');
	i = 0;
	while (cmds[i] != 0)
		i++;
	if (i != pipes)
		deallocate("Error> invalid pipes.");
	ms->cmd = malloc(sizeof(t_cmd) * i);
	if (!ms->cmd)
		deallocate("Error> invalid pipes.");
	i = 0;

	while (cmds != 0 && i != pipes)
	{
		redirections(ms, cmds[i]);
		ms->cmd[i].cmd = cmds[i];

	}

}

t_ms	*init_ms(char *str, int pipes)
{
	t_ms *ms;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		deallocate("Error> failed memory allocation for t_ms.");
	ms->cmd = malloc(sizeof(t_cmd));
	if (!ms->cmd)
		deallocate("Error> failed memory allocation for t_cmd.");
	ms->cmd = str;
	parse_pipes(ms, str, pipes);
}

void	parse_input(char *str)
{
	// t_ms	*ms;
	// //quote_validator(str);
	// ms = init_ms(str, pipe_counter(str));
	ft_printf("%d\n", pipe_counter(str));
}