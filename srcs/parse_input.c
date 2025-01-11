/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/10 17:44:44 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	pipe_counter(char *str)
{
	int	pipes;
	int	quote;

	pipes = 0;
	quote = 0;
	while(str)
	{
		if (*str == '"' && quote == 1)
			quote = 0;
		else if (*str == '"')
			quote = 1;
		if (*str == '|' && quote == 0)
		{
			//new_pipe();
			pipes++;
		}
		str++;
	}
	return (pipes);
}

void	quote_validator(char *str)
{
	int	quote;

	quote = 0;
	while(str)
	{
		if (*str == '"' && quote == 1)
			quote = 0;
		else if (*str == '"')
			quote = 1;
		str++;
	}
	if (quote == 1)
		deallocate("Error> invalid number of quotes.\n");
}

void	parse_input(char *str)
{
	quote_validator(str);
	ft_printf("%d\n", pipe_counter(str));
}