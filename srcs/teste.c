/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:42:31 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/14 01:05:52 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

typedef struct s_lst
{
	char	*str;
	struct s_lst	*next;
}				t_lst;

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

int	main(void)
{
	int		i = 0;
	t_lst	*new_node;
	t_lst	*list;
	t_lst	dummy;
	t_lst	*temp;

	while (i < 5)
	{
		new_node = malloc(sizeof(t_lst));
		new_node->str = ft_strjoin(ft_strdup("node "), ft_itoa(i));
		new_node->next = NULL;
		if (!list)
			list = new_node;
		else
		{
			ft_printf("hello\n");
			temp = get_last_node(list, get_offset(&dummy, &dummy.next));
			temp->next = new_node;
		}
		i++;
	}
	temp = list;
	while (temp != NULL)
	{
		ft_printf("Str: %s\n", temp->str);
		temp = temp->next;
	}
}