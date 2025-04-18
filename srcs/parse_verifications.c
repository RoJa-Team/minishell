/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_verifications.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:42:23 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/18 20:15:04 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_quotes(char *input)
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
		return (bad_input("Syntax error: incorrect number of \
quotes!\n", 2), 1);
	return (0);
}

int	verify_heredocs(char *input)
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
		return (bad_input("Syntax error: maximum here-document \
count exceeded!\n", 2), 1);
	return (0);
}

int	verify_redirections(char *input)
{
	int	i;
	int	len;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			i = i + within_quotes(&input[i]);
		else if (input[i] == '<' || input[i] == '>')
		{
			len = 0;
			while (input[i] && input[i] == input[i + len])
				len++;
			i = i + len;
			while (input[i] && input[i] == ' ')
				i++;
			if (len > 2 || check_metachar(input[i]) || input[i] == '\0')
				return (bad_input("Syntax error: invalid redirection!\n", \
					2), 1);
		}
		else
			i++;
	}
	return (0);
}

int	verify_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			i = i + within_quotes(&input[i]);
		else if (input[i] == '|')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '\0')
				return (bad_input("Syntax error: invalid pipe!\n", \
					2), 1);
		}
		else
			i++;
	}
	return (0);
}

int	verify_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (1);
	if (verify_quotes(input) || verify_redirections(input) || \
	verify_heredocs(input) || verify_pipes(input))
		return (1);
	return (0);
}
