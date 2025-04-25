/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:33:30 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/25 19:22:12 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	setup_parse(void)
{
	setup_signal(SIGINT, parse_signal, SA_RESTART);
	setup_signal(SIGQUIT, SIG_IGN, 0);
}

void	setup_exec(void)
{
	setup_signal(SIGINT, exec_signal, SA_RESTART);
	setup_signal(SIGQUIT, exec_signal, SA_RESTART);
}

void	setup_heredoc(void)
{
	setup_signal(SIGINT, heredoc_signal, SA_RESTART);
	rl_event_hook = rl_hook;
}

void	setup_signal(int signum, void (*sig_handler)(int), int flag)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sa.sa_flags = flag;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ((void)(catch()->error_msg = "Failed setting up signals"));
	if (sigaction(signum, &sa, NULL) != 0)
		return ((void)(catch()->error_msg = "Failed setting up signals"));
}
