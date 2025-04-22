/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:44:27 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/22 18:29:28 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	setup_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_signal;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
		deallocate("Error: Failed heredoc siganls\n");
}

void	heredoc_signal(int signal)
{
	(void)signal;
	ms()->here_sig = 1;
	write(1, "\n", 1);
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
