/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:43:14 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/30 15:51:52 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int len)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && i < len)
		i++;
	new_str = malloc(sizeof(char) * i + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
