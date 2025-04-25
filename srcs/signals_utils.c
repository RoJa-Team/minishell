/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:44:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/25 19:22:12 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	heredoc_signal(int signal)
{
	(void)signal;
	ms()->here_sig = 1;
	write(1, "\n", 1);
}

void	parse_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	ms()->exit_status = 130;
}

void	exec_signal(int signal)
{
	if (signal == SIGQUIT)
		ms()->exit_status = 131;
	if (signal == SIGINT)
		ms()->exit_status = 130;
}

int	rl_hook(void)
{
	if (ms()->here_sig)
	{
		rl_done = 1;
		rl_event_hook = 0;
	}
	return (0);
}
