/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:33:30 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/18 22:29:49 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	signal_handler(int signal)
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

void	setup_signals(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sig.sa_handler = signal_handler;
	if (sigemptyset(&sig.sa_mask) != 0)
		return ((void)ft_printf("Error: Failed cleaning mask."));
	if (sigaction(SIGINT, &sig, NULL) != 0)
		return ((void)ft_printf("Error: Failed assigning action to SIGINT."));
	sig.sa_flags = 0;
	sig.sa_handler = SIG_IGN;
	if (sigemptyset(&sig.sa_mask) != 0)
		return ((void)ft_printf("Error: Failed cleaning mask."));
	if (sigaction(SIGQUIT, &sig, NULL) != 0)
		return ((void)ft_printf("Error: Failed assigning action to SIGQUIT."));
}

void	exec_signal(int signal)
{
	if (signal == SIGQUIT)
		ms()->exit_status = 131;
	if (signal == SIGINT)
		ms()->exit_status = 130;
}

void	setup_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = exec_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL))
		deallocate("Error: FAiled at execution mode in SIGINT\n");
	if (sigaction(SIGQUIT, &sa, NULL))
		deallocate("Error: FAiled at execution mode in SIGQUIT\n");
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
