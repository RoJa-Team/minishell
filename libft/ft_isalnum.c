/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:30:02 by rafasant          #+#    #+#             */
/*   Updated: 2024/02/19 15:52:50 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("A: %d\n", ft_isalnum('A'));
// 	printf("Z: %d\n", ft_isalnum('Z'));
// 	printf("< A: %d\n", ft_isalnum('@'));
// 	printf("> Z: %d\n", ft_isalnum('['));
// 	printf("a: %d\n", ft_isalnum('a'));
// 	printf("z: %d\n", ft_isalnum('z'));
// 	printf("< a: %d\n", ft_isalnum('`'));
// 	printf("> z: %d\n", ft_isalnum('{'));
// 	printf("0: %d\n", ft_isalnum('0'));
// 	printf("9: %d\n", ft_isalnum('9'));
// 	printf("< 0: %d\n", ft_isalnum('/'));
// 	printf("> 9: %d\n", ft_isalnum(':'));
// }