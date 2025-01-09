/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:14:11 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/21 17:41:31 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

// int	main(void)
// {
// 	t_list	*lst;

// 	//ft_lstadd_back(&lst, NULL);
// 	lst = NULL;
// 	//lst = malloc(sizeof(t_list));
// 	//ft_lstadd_back(&lst, ft_lstnew((void*)1));
// 	//lst = ft_lstnew((void*)1);
// 	// doesn't work without this - if it's the first node of the list, 
//should it just be added like in addfront?
// 	ft_lstadd_back(&lst, ft_lstnew((void*)2));
// 	ft_lstadd_back(&lst, ft_lstnew((void*)3));
// 	printf("%lu\n", (unsigned long int)lst->content);
// 	printf("%lu\n", (unsigned long int)lst->next->content);
// 	printf("%lu\n", (unsigned long int)lst->next->next->content);
// }