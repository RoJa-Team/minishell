/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:12:37 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/19 23:49:32 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] != '\0' && len > 0)
	{
		j = 0;
		while ((big[i + j] == little[j]) && (big[i + j] != '\0') && len - j > 0)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		len--;
		i++;
	}
	return (NULL);
}

// #include <string.h>

// int	main(void)
// {
// 	char	*big;
// 	char	*little;

// 	big = "hello there";
// 	little = " ";
// 	printf("%s\n", ft_strnstr(big, little, 5));
// }