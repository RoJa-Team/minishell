/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/05 16:07:26 by rafasant         ###   ########.fr       */
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
			return (ft_printf("exit\n"), clean_structs(), 0);
		if (input[0] != ' ' && input[0] != '\0')
			add_history(input);
		if (input[0] != '\0')
			input_check(input);
	}
	return (0);
}
