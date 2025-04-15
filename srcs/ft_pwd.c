/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 03:24:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/15 20:55:31 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_pwd(void)
{
	ft_putstr_fd(ms()->exec->pwd, 1);
	ft_putchar_fd('\n', 1);
/*	
	char	*cwd;
	size_t	buffer_size;

	buffer_size = 1024;
	cwd = malloc(sizeof(char) * buffer_size);
	if (getcwd(cwd, buffer_size) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		free(cwd);
	}
	else
		perror("getcwd() error\n");
		*/
	ms()->exit_status = 0;
}
