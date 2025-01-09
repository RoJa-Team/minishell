/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:57:55 by rafasant          #+#    #+#             */
/*   Updated: 2024/02/20 12:53:16 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len != 0)
	{
		*p = c;
		len--;
		p++;
	}
	return (b);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*str;

// 	str = malloc(sizeof(char) * 6);
// 	ft_memset(str, 'h', 6);
// 	while (*str != '\0')
// 	{
// 		printf("%c\n", *str);
// 		str++;
// 	}
// }