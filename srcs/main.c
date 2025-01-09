/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:50:32 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/09 12:38:15 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
	if (argc != 1)
		return (ft_printf("Error: invalid number of arguments."));
	while (1)
	{

	}
}
/* 
main(argc, argv, env[]):
init tudo + env (copia do env bash)
shell loop
	[] sinais
	[] input 
		[]- readline
		[] parsing
			[] tokenization
				[] space
				[] ""
				[] ' '
				[] symbol ls a"wc"
				ec"ho " hello < dasasfda  | cat << eof | pwd | echo abc | ls < cat
			[] sintax error
			[] expansao
				[] remove quote
			[] heredoc
		[]execute
			[] builtins
			[] execve 
		[] free 
 */