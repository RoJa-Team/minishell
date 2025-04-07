/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:56:58 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/07 20:38:14 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	within_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	i++;
	while (str[i] && str[i] != c)
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
