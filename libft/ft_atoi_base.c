/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 01:40:32 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/04 16:53:20 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	if (!base || ft_strlen(base) < 2)
		return (1);
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+' || base[i] == ' ' || \
		(base[i] >= 9 && base[i] <= 13))
			return (1);
		j = 1;
		while (base[i + j] != '\0')
		{
			if (base[i] == base[i + j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	flag;
	int	n;

	if (check_base(base) == 0 && str)
	{
		i = 0;
		while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
			i++;
		flag = 1;
		while (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		{
			if (str[i] == '-')
				flag = flag * -1;
			i++;
		}
		n = 0;
		while (get_index(str[i], base) != -1)
			n = n * ft_strlen(base) + get_index(str[i++], base);
		return (n * flag);
	}
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_atoi_base(" \n \t \r ++--+---+1234", "1234"));
// 	printf("%d\n", ft_atoi_base(" ---+-abc + 893 --", "0123456789abcdef"));
// 	printf("%d\n", ft_atoi_base("  ---+-223bc + 893 ---", "012345"));
// 	printf("%d\n", ft_atoi_base("  ----+-123 + 893 --", "0123"));
// 	printf("%d\n", ft_atoi_base(" ---+--2147483648", "0123456789"));
// 	printf("%d\n", ft_atoi_base("  ----+-11101101 + 893 --", "01"));
// 	printf("%d\n", ft_atoi_base("  ----+-122 + 893 --", "012345678"));
// 	printf("%d\n", ft_atoi_base("  -----+-rafael + 893 --", "rafel"));
// }