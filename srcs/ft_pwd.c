/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 03:24:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/02/04 04:22:14 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_pwd(t_ms *ms)
{
	int	fd = 1;

	while (ms->env_lst != NULL)
	{
		if (ft_strncmp(ms->env_lst->key, "PWD", 3) == 0)
		{	
			ft_putstr_fd(ms->env_lst->value, fd);
			ft_putchar_fd('\n', fd);
			break ;
		}
		ms->env_lst = ms->env_lst->next;
	}
	return (1);
}
