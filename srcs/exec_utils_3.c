/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:00:32 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/01 21:31:06 by joafern2         ###   ########.fr       */
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

void	remove_key(t_env *prev, t_env *temp, char *arg)
{
	(void)arg;
	while (temp != NULL)
	{
		if (ft_strncmp(arg, temp->key, ft_strlen(temp->key) + 1) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				ms()->env_lst = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
