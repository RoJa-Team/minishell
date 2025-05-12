/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:36:25 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/12 11:13:51 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_array(char **split_arg)
{
	int	i;

	i = 0;
	while (split_arg[i] != NULL)
	{
		free(split_arg[i]);
		i++;
	}
	free(split_arg);
}

void	bad_input(char *message, int error)
{
	ms()->exit_status = error;
	ft_putstr_fd(message, 2);
	write(2, "\n", 1);
}

void	deallocate(void)
{
	clean_structs();
	ft_putstr_fd(catch()->error_msg, 2);
	exit(1);
}
