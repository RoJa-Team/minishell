/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:47:46 by rafasant          #+#    #+#             */
/*   Updated: 2024/05/15 15:56:09 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set_checker(char c, char	const *set)
{
	int	i;

	i = -1;
	while (set[++i] != '\0')
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	while (ft_set_checker(s1[start], set) && s1[start] != '\0')
		start++;
	end = ft_strlen(s1);
	while (ft_set_checker(s1[end - 1], set) && end > start)
		end--;
	str = malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_strtrim(" well well hello well there wellwell ", "well"));
// }