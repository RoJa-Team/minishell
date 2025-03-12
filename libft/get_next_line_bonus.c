/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:07:40 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/12 21:23:11 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE < 1 || fd > FOPEN_MAX)
		return (NULL);
	if (buffer[fd][0] == '\0')
	{
		if (read(fd, buffer[fd], BUFFER_SIZE) <= 0)
			return (NULL);
	}
	str = gnl_get_str(fd, buffer[fd], NULL);
	if (!str)
		return (NULL);
	return (str);
}
