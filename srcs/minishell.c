/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/15 21:51:07 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// echo 123 | cat -e | wc -l

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_ms	*ms;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error: Invalid number of arguments.\n"));
	ms = init_ms(env);
	while (1)
	{
		input = readline("$minishell>");
		parse_input(ms, input);
		ft_printf("input>%s\n", input);
		add_history(input);
		//execute();
		if (!ft_strncmp(input, "exit", 4))
			break ;
	}
}
