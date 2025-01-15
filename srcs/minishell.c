/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/15 00:34:47 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// echo 123 | cat -e | wc -l
/*
int	main(int argc, char **argv)
{
	char	*input;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error: Invalid number of arguments.\n"));
	while (1)
	{
		input = readline("$minishell>");
		parse_input(input);
		ft_printf("input>%s\n", input);
		add_history(input);
		//execute();
		if (!ft_strncmp(input, "exit", 4))
			break ;
	}
}*/
