/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 03:24:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/26 21:08:13 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_pwd(void)
{
	char	*cwd;
	size_t	buffer_size;
	int	fd = 1;

	buffer_size = 1024;
	cwd = malloc(sizeof(char) * buffer_size);
	if (getcwd(cwd, buffer_size) != NULL)
	{
		ft_putstr_fd(cwd, fd);
		ft_putchar_fd('\n', fd);
	}
	else
		perror("getcwd() error\n");
	/*
	while (ms->env_lst != NULL)
	{
		if (ft_strncmp(ms->env_lst->key, "PWD", 3) == 0)
		{	
			ft_putstr_fd(ms->env_lst->value, fd);
			ft_putchar_fd('\n', fd);
			break ;
		}
		ms->env_lst = ms->env_lst->next;
	}
	*/
	//printf("Sim, é builtin\n");
}
