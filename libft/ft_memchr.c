/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:21:25 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 23:57:32 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n > 0)
	{
		if (*s2 == (unsigned char)c)
			return (s2);
		s2++;
		n--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*s;

// 	s = "hello";
// 	if (ft_memchr(s, 'e', 5) != NULL)
// 		printf("%s\n", "hello");
// }