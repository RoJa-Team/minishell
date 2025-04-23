/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:00:32 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/23 20:01:32 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	execute_builtin_or_execve(int i)
{
	if (is_builtin(i))
	{
		execute_builtin(i);
		clean_structs();
		exit (0);
	}
	else
		execute_execve(i);
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
