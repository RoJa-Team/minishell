/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:27:01 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 20:40:45 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(long int n)
{
	int	nlen;

	if (n == 0)
		return (1);
	nlen = 0;
	if (n < 0)
		nlen++;
	while (n != 0)
	{
		n = n / 10;
		nlen++;
	}
	return (nlen);
}

char	*ft_itoa(int n)
{
	long int	ln;
	int			nlen;
	char		*nstr;

	ln = n;
	nlen = ft_nlen(ln);
	nstr = malloc(sizeof(char) * nlen + 1);
	if (!nstr)
		return (NULL);
	nstr[nlen--] = '\0';
	if (ln < 0)
	{
		ln = -ln;
		nstr[0] = '-';
	}
	while (ln > 9)
	{
		nstr[nlen--] = ln % 10 + '0';
		ln = ln / 10;
	}
	nstr[nlen] = ln % 10 + '0';
	return (nstr);
}

// int	main(void)
// {
// 	char	*str;

// 	str = ft_itoa(-2147483648);
// 	printf("%s\n", str);
// 	free(str);
// 	str = ft_itoa(0);
// 	printf("%s\n", str);
// 	free(str);
// 	str = ft_itoa(2147483647);
// 	printf("%s\n", str);
// 	free(str);
// }