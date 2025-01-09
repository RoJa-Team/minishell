/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:48:21 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/19 23:41:06 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;

	if (!dst && !src)
		return (NULL);
	dest = dst;
	source = src;
	while (n > 0)
	{
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	return (dst);
}

// int	main(void)
// {
// 	char	dest[100];

// 	memset(dest, 'A', 100);
// 	printf("%p\n", ft_memcpy(dest, "coucou", 6));
// 	printf("%s\n", dest);
// 	printf("%p\n", memcpy(dest, "coucou", 6));
// 	printf("%s\n", dest);
// }