/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:07:36 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/09 21:58:42 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*cd_no_file(char *oldpwd, char *newpwd, int i)
{
	free(newpwd);
	newpwd = ft_strdup(oldpwd);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(ms()->cmd[i]->arg[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ms()->cmd[i]->cmd_status = 1;
	return (newpwd);
}

char	*cd_cases(char **split_path, char *ab_path, char *temp, int i)
{
	while (split_path[i])
	{
		if (ft_strncmp(split_path[i], "..", 3) == 0 || \
		ft_strncmp(split_path[i], ".", 2) == 0)
		{
			if (ft_strncmp(split_path[i], "..", 3) == 0)
				temp = get_parent_dir(ab_path);
			else
				temp = ft_strdup(ab_path);
			free(ab_path);
			ab_path = ft_strdup(temp);
			free(temp);
		}
		else if (ab_path[0] == '\0' || ab_path[ft_strlen(ab_path) - 1] != '/')
		{
			temp = ft_strjoin(ab_path, "/");
			if (!temp)
				return ((catch()->error_msg = "Strdup failed"), NULL);
			free(ab_path);
			ab_path = ft_strjoin(temp, split_path[i]);
			free(temp);
		}
		free(split_path[i++]);
	}
	return (ab_path);
}
