/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:40:45 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 23:00:19 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s2;

	if (n == 0)
		return ;
	i = 0;
	s2 = s;
	while (i != n)
	{
		s2[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char	*str;

// 	str = ft_strdup("hello");
// 	printf("%s\n", str);
// 	ft_bzero(str, 5);
// 	printf("%s\n", str);
// }