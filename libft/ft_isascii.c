/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:41:17 by rafasant          #+#    #+#             */
/*   Updated: 2024/02/19 15:52:39 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("\\0: %d\n", ft_isascii('\0'));
// 	printf("DEL: %d\n", ft_isascii(127));
// 	printf("Ç: %d\n", ft_isascii(128));
// 	printf("255: %d\n", ft_isascii(255));
// }