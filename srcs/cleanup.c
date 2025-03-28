/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:34 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/28 21:39:35 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	check_child_exit(t_ms *ms, int status)
{
	ms->exit_status = (status >> 8) & 0xFF;
	ft_printf("Exit status: %d\n", ms->exit_status);
}
