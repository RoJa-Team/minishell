/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:15:39 by rafasant          #+#    #+#             */
/*   Updated: 2024/05/04 15:29:45 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_bzero(array[i], ft_strlen(array[i]));
		free(array[i++]);
	}
	free(array);
	return (NULL);
}

static int	ft_str_count(char const *s, char c)
{
	int	i;
	int	n_words;

	if (!s)
		return (0);
	i = 0;
	n_words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n_words++;
		i++;
	}
	return (n_words);
}

static char	*ft_str(char const *s, int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * n + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*s && i != n)
	{
		str[i++] = *s;
		s++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		nstrs;
	char	**strs;

	strs = malloc(sizeof(char *) * (ft_str_count(s, c) + 1));
	if (!strs || !s)
		return (free(strs), NULL);
	i = 0;
	nstrs = 0;
	while (s[i] != '\0' && nstrs < ft_str_count(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = 0;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		strs[nstrs] = ft_str(&s[i], j);
		if (!strs[nstrs++])
			return (ft_free(strs));
		i = i + j;
	}
	strs[nstrs] = 0;
	return (strs);
}

// int	main(void)
// {
// 	char	**strs;
// 	int		i;

// 	strs = ft_split(NULL, ' ');
// 	if (!strs)
// 		return (printf("%s\n", "Deu nulo"));
// 	i = 0;
// 	while (strs[i] != 0)
// 	{
// 		printf("%s\n", strs[i]);
// 		i++;
// 	}
// 	ft_free(strs);
// }