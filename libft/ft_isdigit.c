/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:27:15 by rafasant          #+#    #+#             */
/*   Updated: 2024/02/19 15:52:33 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("0: %d\n", ft_isdigit('0'));
// 	printf("9: %d\n", ft_isdigit('9'));
// 	printf("< 0: %d\n", ft_isdigit('/'));
// 	printf("> 9: %d\n", ft_isdigit(':'));
// }