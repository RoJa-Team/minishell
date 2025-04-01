/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:56:58 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/01 18:07:05 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// t_ms	*ms(void)
// {
// 	static t_ms	*ms;

// 	if (!ms)
// 		init_ms();

// 	return (ms);
// }

int	within_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	i++;
	while (str[i] != c)
		i++;
	i++;
	return (i);
}

int	check_metachar(char c)// ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, ‘>’, ' , \t, \n
{
	return (c == '|' || c == '<' || c == '>' || c == '\t' || c == '\n' || \
	c == ' ');
}

void	check_quotes(char c, int *quotes)
{
	if (c == '\'' && *quotes == 1)
		*quotes = 0;
	else if (c == '\'' && *quotes == 0)
		*quotes = 1;
	else if (c == '\"' && *quotes == 2)
		*quotes = 0;
	else if (c == '\"' && *quotes == 0)
		*quotes = 2;
}

void	verify_quotes(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input[i])
	{
		check_quotes(input[i], &quotes);
		i++;
	}
	if (quotes != 0)
	{
		debug("verify_quotes", quotes);
		exit(1);
	}
}

void	verify_heredocs(char *input)
{
	int	i;
	int	len;
	int	n_heredoc;

	i = 0;
	n_heredoc = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			i = i + within_quotes(&input[i]);
		else if (input[i] == '<')
		{
			len = 0;
			while (input[i] && input[i + len] == '<')
				len++;
			if (len == 2)
				n_heredoc++;
			i = i + len;
		}
		else
			i++;
	}
	if (n_heredoc > 16)
	{
		debug("verify_heredocs", n_heredoc);
		exit(1);
	}
}

void	verify_input(char *input)
{
	verify_quotes(input);
	verify_heredocs(input);


	
}
