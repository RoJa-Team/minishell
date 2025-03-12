/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:22:10 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/12 21:12:23 by rafasant         ###   ########.fr       */
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
	print_env_lst(ms);
	print_ms_env(ms);
	while (1)
	{
		input = readline("$minishell>");
		if (input[0] != ' ' && input[0] != '\0')
			add_history(input);
		if (input[0] != '\0')
		{
			parse_input(ms, input);
			exec_cmd(ms);
			//clean_cmd(ms);
			if (input && !ft_strncmp(input, "exit", 4))
				break ;
		}
	}
	return (0);
}
