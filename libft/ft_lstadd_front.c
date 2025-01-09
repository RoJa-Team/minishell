/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:12:05 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/18 20:30:56 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*lst = NULL;

// 	// ft_lstadd_front(&lst, NULL);
// 	// ft_lstadd_front(NULL, ft_lstnew((void*)1));
// 	ft_lstadd_front(&lst, ft_lstnew((void*)2));
// 	ft_lstadd_front(&lst, ft_lstnew((void*)3));
// 	printf("%p\n", lst->content);
// 	printf("%p\n", lst->next->content);
// 	//printf("%lu\n", (unsigned long int)lst->next->next->content);
// }
