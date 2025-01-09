/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:37:50 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 23:49:22 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
		i++;
	while (dstsize > 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize >= 1)
		*dst = '\0';
	return (i);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	dest[5];
// 	char	dest2[6];
// 	char	*src;
// 	char	*src2;

// 	src = "hello";
// 	src2 = "hello2";
// 	printf("%zu\n", ft_strlcpy(dest, src, 5));
// 	printf("%s\n", dest);
// 	printf("%zu\n", strlcpy(dest2, src2, 6));
// 	printf("%s\n", dest2);
// }