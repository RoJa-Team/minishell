/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:55:57 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/24 22:18:27 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	expansion_len(t_ms *ms, char *str, int *i)
{
	int		len;
	t_env	*temp;

	(*i)++;
	len = 0;
	if (str[*i] == '?')
		len++;
	else if (ft_isdigit(str[*i]))
		deallocate("Error> invalid identifier (envs nao podem comecar com digitos)");
	else
		while (str[*i + len] && !check_metachar(str[*i + len]) && str[*i + len] != '\'' && str[*i + len] != '\"')
			len++;
	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (ft_strlen_c(&str[*i], str[*i + len]) == ft_strlen(temp->key) && !strncmp(&str[*i], temp->key, len))
			break;
		temp = temp->next;
	}
	*i = *i + len;
	if (temp)
		return (ft_strlen(temp->value));
	return (0);
}

int	exp_len(t_ms *ms, char *str)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	check_quotes(str[i], &quotes);
	while (str[i])
	{
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			len = len + expansion_len(ms, str, &i);
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
				len++;
			i++;
		}
		check_quotes(str[i], &quotes);
	}
	return (len);
}

char	*expansion_value(t_ms *ms, char *str, int *i)
{
	int		len;
	t_env	*temp;

	(*i)++;
	len = 0;
	while (str[*i + len] && !check_metachar(str[*i + len]) && str[*i + len] != '\'' && str[*i + len] != '\"')
		len++;
	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (ft_strlen_c(&str[*i], str[*i + len]) == ft_strlen(temp->key) && !strncmp(&str[*i], temp->key, len))
			break;
		temp = temp->next;
	}
	*i = *i + len;
	if (temp)
		return (temp->value);
	return (NULL);
}

char	*expand_str(t_ms *ms, char *str)
{
	int	i;
	int	j;
	int	len;
	int	quotes;
	char	*exp;
	char	*value;

	if (!str)
		return (NULL);
	exp = malloc(sizeof(char) * exp_len(ms, str) + 1);
	if (!exp)
		deallocate ("Error> expand_token");
	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
		{
			value = expansion_value(ms, str, &i);
			j = 0;
			while (value && value[j])
				exp[len++] = value[j++];
		}
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
				exp[len++] = str[i];
			i++;
		}
	}
	exp[len] = '\0';
	return (exp);
}
