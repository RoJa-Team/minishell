/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:05:51 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/11 20:55:56 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	sort_env(char **env)
{
	int	i;
	int	j;
	int	size;
	int	max_size;

	i = 0;
	size = 0;
	while (env[size])
		size++;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strlen(env[j]) > ft_strlen(env[j + 1]))
				max_size = ft_strlen(env[j]);
			else
				max_size = ft_strlen(env[j + 1]);
			if (ft_strncmp(env[j], env[j + 1], max_size + 1) > 0)
				swap_str(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

void	print_export_fd(t_ms *ms)
{
	int		i;
	char	**env;
	int		fd;

	fd = 1;
	env = ms->ms_env;
	sort_env(env);
	i = 0;
	while (env[i])
	{
		execute_export(fd, env[i]);
		i++;
	}
}

void	execute_export(int fd, char *line)
{
	char	*equal;

	ft_putstr_fd("declare -x ", fd);
	equal = ft_strchr(line, '=');
	if (equal)
	{
		write(fd, line, equal - line);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(equal + 1, fd);
		ft_putstr_fd("\"\n", fd);
	}
	else
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_export(t_ms *ms, int i)
{
	char	**arg;
	int		j;

	j = 1;
	arg = ms->cmd[i]->arg;
	if (!arg[j])
		print_export_fd(ms);
	else
		add_new_key(ms, arg, j);
}

void	add_new_key(t_ms *ms, char **arg, int j)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	while (arg[j])
	{
		get_key_and_value(ms, arg[j], &key, &value);
		if (!is_valid_key(key))
			ft_printf("export: %s: not a valid identifier\n", arg[j]);
		else
			update_or_add_env_key(&ms->env_lst, key, value);
		free_key_and_value(key, value);
		j++;
	}
	update_ms_env(ms);
}
