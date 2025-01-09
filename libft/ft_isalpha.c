/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:06:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/20 00:39:31 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("A: %d\n", ft_isalpha('A'));
// 	printf("Z: %d\n", ft_isalpha('Z'));
// 	printf("a: %d\n", ft_isalpha('a'));
// 	printf("z: %d\n", ft_isalpha('z'));
// 	printf("< A: %d\n", ft_isalpha('@'));
// 	printf("> Z: %d\n", ft_isalpha('['));
// 	printf("< a: %d\n", ft_isalpha('`'));
// 	printf("> z: %d\n", ft_isalpha('{'));
// }