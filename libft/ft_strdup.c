/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:15:28 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/19 23:54:30 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*s;
	int		i;

	s = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = ft_strdup("hello");
// 	printf("%s\n", str);
// }