/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:30:12 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/21 17:42:29 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// static void	ft_char(unsigned int i, char *c)
// {
// 	*c = *c + i;
// }

// int	main(void)
// {
// 	char	s[] = "hello there!";

// 	ft_striteri(s, ft_char);
// 	printf("%s\n", s);
// }