/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_expansions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/18 20:30:54 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	here_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			len = len + ft_strlen(expansion_value(line, &i));
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*final_here(char *str, char *arg, int i)
{
	int		j;
	char	*val;

	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			val = expansion_value(str, &i);
			ft_strlcat(&arg[j], val, ft_strlen(arg) + ft_strlen(val) + 1);
			j = j + ft_strlen(val);
		}
		else
		{
			arg[j++] = str[i];
			i++;
		}
	}
	arg[j] = '\0';
	return (arg);
}

char	*expand_here(char *line)
{
	int		len;
	char	*arg;

	if (!line)
		return (NULL);
	len = here_len(line);
	if (len == 0)
		return (free(line), NULL);
	arg = ft_calloc(sizeof(char), len + 1);
	if (!arg)
		deallocate ("Memory allocation error: expand_here\n");
	arg = final_here(line, arg, 0);
	free(line);
	return (arg);
}
