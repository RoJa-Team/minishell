/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:34:57 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/04 16:53:35 by rafasant         ###   ########.fr       */
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

char	*ft_ltoa(long n)
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
