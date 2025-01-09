/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:06:57 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/23 14:49:39 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// void	del(void *content)
// {
// 	(void)content;
// 	return ;
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*temp;
// 	int		i;

// 	lst = NULL;
// 	i = 0;
// 	while (i < 5)
// 	{
// 		ft_lstadd_back(&lst, ft_lstnew((void *)(int *)1 + i));
// 		i++;
// 	}
// 	temp = lst;
// 	i = 0;
// 	while (i++ < 3)
// 		temp = temp->next;
// 	ft_lstdelone(temp, del);
// 	while (lst != NULL)
// 	{
// 		printf("Before: %lu\n", (unsigned long int)lst->content);
// 		lst = lst->next;
// 		i++;
// 	}
// }