/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 03:24:56 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/22 18:57:06 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_pwd(void)
{
	ft_putstr_fd(ms()->exec->pwd, 1);
	ft_putchar_fd('\n', 1);
	ms()->exit_status = 0;
}

int	is_executable(const char *path)
{
	struct stat	st;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	return (1);
}
