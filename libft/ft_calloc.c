/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:27 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/23 14:50:43 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	value;

	value = nmemb * size;
	if (value && (value / size) != nmemb)
		return (NULL);
	array = malloc(value);
	if (!array)
		return (NULL);
	ft_memset(array, 0, value);
	return (array);
}

// int	main(void)
// {
// 	char	*str;
// 	int		*array;
// 	int	i;

// 	i = 0;
// 	str = ft_calloc(5, 1);
// 	while (i < 4)
// 	{
// 		str[i] = 'a' + i;
// 		i++;
// 	}
// 	str[i] = '\0';
// 	printf("%s\n", str);
// 	i = 0;
// 	array = ft_calloc(5, 4);
// 	while (i < 5)
// 	{
// 		array[i] = i;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 7)
// 		printf("%d\n", array[i++]);
// }