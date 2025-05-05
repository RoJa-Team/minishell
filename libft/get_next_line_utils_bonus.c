/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:07:15 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/12 21:26:15 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_ft_strlen_c(char *str, char c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (i);
}

char	*gnl_ft_strndup(char *str, int len)
{
	char	*s;
	int		i;

	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len && str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*gnl_ft_strjoin_n(char *s1, char *s2, int len)
{
	char	*s;
	int		i;
	int		j;

	if (!s1)
		return (gnl_ft_strndup(s2, len));
	if (!s2)
		return (s1);
	s = malloc(sizeof(char) * (gnl_ft_strlen_c(s1, '\0') + len) + 1);
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		s[i] = s1[i];
	j = -1;
	while (++j != len)
		s[i + j] = s2[j];
	s[i + j] = '\0';
	free(s1);
	return (s);
}

void	gnl_adjust_buffer(char *buffer, int len)
{
	int		i;
	int		j;

	if (len == 0)
		return ;
	i = 0;
	while (i != len)
	{
		buffer[i] = '\0';
		i++;
	}
	if (len == BUFFER_SIZE)
		return ;
	j = 0;
	while (i + j != BUFFER_SIZE)
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	while (j != BUFFER_SIZE)
	{
		buffer[j] = '\0';
		j++;
	}
}

char	*gnl_get_str(int fd, char *buffer, char *str)
{
	int		len;
	int		n_read;

	n_read = 1;
	while (n_read != 0)
	{
		if (n_read == -1)
			return (free(str), NULL);
		len = 0;
		while (len != BUFFER_SIZE && buffer[len] != '\n')
			len++;
		if (len != BUFFER_SIZE && buffer[len] == '\n')
			len++;
		str = gnl_ft_strjoin_n(str, buffer, len);
		if (!str)
			return (NULL);
		gnl_adjust_buffer(buffer, len);
		if (str[gnl_ft_strlen_c(str, '\n')] == '\n')
			break ;
		n_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}
