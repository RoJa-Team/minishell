/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:53:29 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/20 00:14:53 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("hello: %zu\n", ft_strlen("hello"));
// 	printf("\"\":%zu\n", ft_strlen(""));
// 	printf("\\n: %zu\n", ft_strlen("\n"));
// 	printf("NULL: %zu\n", ft_strlen(NULL));
// }