/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/23 21:57:03 by joafern2         ###   ########.fr       */
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
		setup_parse();
		input = readline("$minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			return (clean_structs(), 0);
		}
		if (input[0] != ' ' && input[0] != '\0')
			add_history(input);
		if (input[0] != '\0')
			input_check(input);
	}
	return (0);
}
