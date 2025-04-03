/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:33:30 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/02 22:11:10 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == 3)
	{
		clean_structs();
		exit(1);
	}
}

void	setup_signals(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = signal_handler;
	if (sigemptyset(&sig.sa_mask) != 0)
		return ((void)ft_printf("Error: Failed cleaning mask."));
	if (sigaction(SIGINT, &sig, NULL) != 0)
		return ((void)ft_printf("Error: Failed assigning action to SIGINT."));
	if (sigaction(SIGQUIT, &sig, NULL) != 0)
		return ((void)ft_printf("Error: Failed assigning action to SIGQUIT."));
}
