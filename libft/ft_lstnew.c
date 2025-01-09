/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:47:38 by rafasant          #+#    #+#             */
/*   Updated: 2024/04/21 17:42:09 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// int	main(void)
// {
// 	t_list	*list;
// 	t_list	*temp;
// 	int		i;

// 	i = 0;
// 	list = ft_lstnew((void*)1234234);
// 	temp = list;
// 	while (i < 3)
// 	{
// 		temp->next = ft_lstnew((void*)1234234 + i + 1);
// 		temp = temp->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 4)
// 	{
// 		printf("%lu\n", (unsigned long int)list->content);
// 		list = list->next;
// 		i++;
// 	}
// }