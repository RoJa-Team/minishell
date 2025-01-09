/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:56:54 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/20 00:14:58 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize <= dlen)
		return (dstsize + slen);
	i = 0;
	while (src[i] != '\0' && dstsize > dlen + i + 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	dest[13];
// 	char	dest2[15];
// 	//char	*dest = "goodbye";
// 	//char	*dest2 = "goodbye2";
// 	char	*src = "hello";
// 	char	*src2 = "hello2";

// 	dest[0] = 'g';
// 	dest[1] = 'o';
// 	dest[2] = 'o';
// 	dest[3] = 'd';
// 	dest[4] = 'b';
// 	dest[5] = 'y';
// 	dest[6] = 'e';
// 	dest[7] = '\0';
// 	dest2[0] = 'g';
// 	dest2[1] = 'o';
// 	dest2[2] = 'o';
// 	dest2[3] = 'd';
// 	dest2[4] = 'b';
// 	dest2[5] = 'y';
// 	dest2[6] = 'e';
// 	dest2[7] = '2';
// 	dest2[8] = '\0';
// 	printf("%zu\n", ft_strlcat(dest, src, 13));
// 	printf("%s\n", dest);
// 	printf("%zu\n", strlcat(dest2, src2, 15));
// 	printf("%s\n", dest2);
// 	return (0);
// }