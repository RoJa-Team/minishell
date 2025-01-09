/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 02:22:49 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 22:57:38 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

// int	main(void)
// {
// 	t_list	*lst;
// 	int		i;

// 	lst = ft_lstnew((void*)0);
// 	i = 0;
// 	while (i < 5)
// 	{
// 		ft_lstadd_back(&lst, ft_lstnew((void*)1 + i));
// 		i++;
// 	}
// 	printf("Size: %d\n", ft_lstsize(lst));
// 	while (lst != NULL)
// 	{
// 		printf("%lu\n", (unsigned long int)lst->content);
// 		lst = lst->next;
// 	}
// }