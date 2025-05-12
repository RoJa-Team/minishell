/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 17:06:01 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: Invalid number of arguments.\n", 2), 1);
	init(env);
	if (catch()->error_msg != NULL)
		deallocate();
	input = NULL;
	while (1)
	{
		setup_parse();
		if (catch()->error_msg != NULL)
			deallocate();
		input = readline("$minishell> ");
		if (!input)
			return (ft_putstr_fd("exit\n", 2), clean_structs(), 0);
		if (input[0] != ' ' && input[0] != '\0')
			add_history(input);
		if (input[0] != '\0')
			input_check(input);
		else
			free(input);
	}
	return (0);
}
