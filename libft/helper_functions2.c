/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:04:42 by rafasant          #+#    #+#             */
/*   Updated: 2024/05/27 14:34:03 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long int n, char *base_to)
{
	unsigned long int	base_len;
	int					total;

	total = 0;
	base_len = ft_strlen(base_to);
	if (n >= base_len)
		total = total + ft_putptr(n / base_len, base_to);
	return (total + write(1, &base_to[n % base_len], 1));
}

int	ft_itoa_base(long int n, char *base_to)
{
	int		base_len;
	int		total;
	int		flag;

	base_len = ft_strlen(base_to);
	flag = 0;
	total = 0;
	if (n < 0)
	{
		n = -n;
		flag = -1;
		total = write(1, "-", 1);
	}
	if (n >= base_len)
		total = total + ft_putptr(n / base_len, base_to);
	if (flag == -1)
		return (total + write(1, &base_to[n % base_len], 1));
	return (total + write(1, &base_to[n % base_len], 1));
}
