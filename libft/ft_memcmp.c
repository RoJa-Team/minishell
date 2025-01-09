/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:57:44 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 22:57:28 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*_s1;
	unsigned char	*_s2;

	if (n == 0)
		return (0);
	_s1 = (unsigned char *)s1;
	_s2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*_s1 != *_s2)
			return (*_s1 - *_s2);
		_s1++;
		_s2++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = "hello there";
// 	s2 = "hello*there";
// 	if (ft_memcmp(s1, s2, 11) > 0)
// 		return (printf("%s\n", "s1 maior que s2"));
// 	if (ft_memcmp(s1, s2, 11) == 0)
// 		return (printf("%s\n", "s1 igual a s2"));
// 	if (ft_memcmp(s1, s2, 11) < 0)
// 		return (printf("%s\n", "s1 menor que s2"));
// }