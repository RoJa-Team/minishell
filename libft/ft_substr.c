/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:43 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/23 14:54:35 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (ft_strdup(""));
	str_len = ft_strlen(s);
	if (!s || str_len == 0 || start > str_len)
		return (ft_strdup(""));
	str_len = ft_strlen(&s[start]);
	if (str_len < len)
		len = str_len;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i != len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// int	main(void)
// {
// 	char	*s;

// 	 s = "tripouille";
// 	s = ft_substr(s, 0, 42000);
// 	printf("%s\n", s);
// }