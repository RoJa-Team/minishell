/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:23:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/27 19:20:43 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

size_t	get_offset(void *struct_ptr, void *member_ptr)
{
	return ((size_t)((char *)member_ptr - (char *)struct_ptr));
}

void	*get_last_node(void *node, size_t next_offset)
{
	char	*tmp;

	tmp = (char *)node;
	if (!tmp)
		return (NULL);
	while (*(void **)(tmp + next_offset))
		tmp = *(char **)(tmp + next_offset);
	return ((void *)tmp);
}

void	free_list(void *node, size_t next_offset)
{
	char	*tmp;

	tmp = (char *)node;
	if (!tmp)
		return;
	while (*(void **)(tmp + next_offset))
	{
		//node = (char *)(tmp + next_offset);
		tmp = *(char **)(tmp + next_offset);
		//ft_printf("%p\n", tmp + next_offset);
	}
}