/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 03:24:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/01 20:52:35 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_pwd(void)
{
	char	*cwd;
	size_t	buffer_size;
	int		fd;

	fd = 1;
	buffer_size = 1024;
	cwd = malloc(sizeof(char) * buffer_size);
	if (getcwd(cwd, buffer_size) != NULL)
	{
		ft_putstr_fd(cwd, fd);
		ft_putchar_fd('\n', fd);
	}
	else
		perror("getcwd() error\n");
	ms()->exit_status = 0;
}
