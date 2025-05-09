/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:35:33 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/09 21:32:42 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*convert_exit_status(void)
{
	int			i;
	char		*str;
	static char	exit_status[10];

	str = ft_itoa(ms()->exit_status);
	if (!str)
		return (catch()->error_msg = \
		"Memory allocation error: convert_exit_status\n", NULL);
	i = 0;
	while (exit_status[i] != '\0')
	{
		exit_status[i] = '\0';
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		exit_status[i] = str[i];
		i++;
	}
	free(str);
	return (exit_status);
}

char	*find_env_value(char *str, int i, int key_len)
{
	t_env	*temp;

	if (key_len > 0 && !ft_strncmp(&str[i], "?", key_len))
		return (convert_exit_status());
	temp = ms()->env_lst;
	while (temp != NULL)
	{
		if (ft_strlen_c(&str[i], str[i + key_len]) == ft_strlen(temp->key) && \
		!ft_strncmp(&str[i], temp->key, key_len))
			break ;
		temp = temp->next;
	}
	if (temp && temp->value)
		return (temp->value);
	return (NULL);
}

char	*expansion_value(char *str, int *i, int flag)
{
	int		len;
	char	*env_value;

	(*i)++;
	len = 0;
	if (str[*i] == '?')
		len++;
	else if (ft_isdigit(str[*i]))
		len++;
	else
		while (str[*i + len] && (ft_isalnum(str[*i + len]) || \
		str[*i + len] == '_'))
			len++;
	*i = *i + len;
	env_value = find_env_value(str, *i - len, len);
	if (flag == 1 && env_value == NULL)
		return ("");
	return (env_value);
}
