/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/18 22:27:56 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error: Invalid number of arguments.\n"));
	init(env);
	input = NULL;
	while (1)
	{
		setup_signals();
		input = readline("$minishell> ");
		if (!input)
			return (clean_structs(), 0);
		if (input[0] != ' ' && input[0] != '\0')
			add_history(input);
		if (input[0] != '\0')
		{
			if (verify_input(input) == 0)
			{
				parse_input(input);
				if (!ms()->here_sig)
					exec_cmd();
				ms()->here_sig = 0;
				clean_cmd();
			}
			free(input);
		}
	}
	return (0);
}
