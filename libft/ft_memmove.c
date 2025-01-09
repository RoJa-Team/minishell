/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:51:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/23 14:50:41 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*source;

	if (!dst && !src)
		return (NULL);
	dest = dst;
	source = src;
	if (dst <= src)
	{
		while (len-- != 0)
			*dest++ = *source++;
	}
	else
	{
		dest = dest + len;
		source = source + len;
		while (len-- != 0)
			*--dest = *--source;
	}
	return (dst);
}

// int	main(void)
// {
// 	char s[] = {65, 66, 67, 68, 69, 0, 45};
// 	char s0[] = { 0,  0,  0,  0,  0,  0, 0};
// 	char sCpy[] = {65, 66, 67, 68, 69, 0, 45};
// 	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
// 	char sResult2[] = {67, 67, 68, 68, 69, 0, 45};

// 	if (ft_memmove(s0, s, 7) == s0 && !memcmp(s, s0, 7))
// 		printf("%s\n", "1");
// 	if (ft_memmove(s, s + 2, 0) && !memcmp(s, sCpy, 7))
// 		printf("%s\n", "2");
// 	if (ft_memmove(s, s + 2, 2) == s && !memcmp(s, sResult, 7))
// 		printf("%s\n", "3");
// 	if (ft_memmove(sResult + 1, sResult, 2) == sResult + 1 
//&& !memcmp(sResult, sResult2, 7))
// 		printf("%s\n", "4");
// }