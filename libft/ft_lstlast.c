/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 02:35:16 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/17 23:20:22 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
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
// 	printf("Last: %lu\n", (unsigned long int)ft_lstlast(lst)->content);
// }