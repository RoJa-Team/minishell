/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/26 22:06:38 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_ms	*ms;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error: Invalid number of arguments.\n"));
	ms = init_ms(env);
	setup_signals();
	input = NULL;
	while (1)
	{
		input = readline("$minishell>");
		if (!input)
			break ;
		if (input[0] != ' ' && input[0] != '\0')
			add_history(input);
		if (input[0] != '\0')
		{
			verify_quotes(input);
			parse_input(ms, input);
			exec_cmd(ms);
			clean_cmd(ms);
			free(input);
		}
	}
	return (0);
}
