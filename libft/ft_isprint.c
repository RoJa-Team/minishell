/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:26:33 by rafasant          #+#    #+#             */
/*   Updated: 2024/02/19 15:52:45 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= 126)
		return (1);
	return (0);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("Space: %d\n", ft_isprint(' '));
// 	printf("~: %d\n", ft_isprint(126));
// 	printf("31: %d\n", ft_isprint(31));
// 	printf("Del: %d\n", ft_isprint(127));
// }