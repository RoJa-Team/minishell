/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/27 22:25:49 by joafern2         ###   ########.fr       */
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
	//print_ms_env(ms);
	//print_env_lst(ms);
	while (1)
	{
		input = readline("$minishell>");
		if (input[0] != ' ')
			add_history(input);
		parse_input(ms, input);
		exec_cmd(ms);
		clean_parse(ms);
		clean_cmd(ms);
		if (input && !ft_strncmp(input, "exit", 4))
			break ;
	}
	return (0);
}
