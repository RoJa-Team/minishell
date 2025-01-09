/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 02:59:47 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/21 22:07:49 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = temp->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*temp;
// 	int		i;

// 	lst = ft_lstnew((void*)0);
// 	i = 0;
// 	while (i < 5)
// 	{
// 		ft_lstadd_back(&lst, ft_lstnew((void*)1 + i));
// 		i++;
// 	}
// 	temp = lst;
// 	while (temp != NULL)
// 	{
// 		printf("Before: %lu\n", (unsigned long int)temp->content);
// 		temp = temp->next;
// 		i++;
// 	}
// 	i = 0;
// 	temp = lst;
// 	while (i < 3)
// 	{
// 		temp = temp->next;
// 		i++;
// 	}
// 	//t_list	*tempprev;
// 	//t_list	*tempafter;
// 	//tempprev = temp;
// 	//temp = temp->next;
// 	//tempafter = temp->next;
// 	ft_lstclear(&temp, del);
// 	//tempprev->next = NULL;
// 	//printf("tempprev: %lu\n", (unsigned long int)tempprev->content);
// 	//printf("tempafter: %lu\n", (unsigned long int)tempafter->content);
// 	while (lst != NULL)
// 	{
// 		printf("After: %lu\n", (unsigned long int)lst->content);
// 			lst = lst->next;
// 		i++;
// 	}
// }