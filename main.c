/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:50:32 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/06 21:13:49 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	write(1, "afe d hello\n", 12);
	write(1, "af d hllo\n", 10);
}
/* 
main(argc, argv, env[]):
init tudo + env (copia do env bash)
shell loop
	[] sinais
	[] input
		[] parsing
			[] tokenization
				[] space
				[] ""
				[] ' '
				[] symbol ls a"wc"
				ec"ho " hello < dasasfda  | cat << eof | pwd | echo abc | ls
			[] sintax error
			[] expansao
				[] remove quote
			[] heredoc
		[]execute
			[] builtins
			[] execve 
		[] free 
 */