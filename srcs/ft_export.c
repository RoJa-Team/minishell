/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:05:51 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/08 21:14:39 by rafasant         ###   ########.fr       */
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

void	add_new_key(char **arg, int j, int i)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	while (arg[j] && catch()->error_msg == NULL)
	{
		get_key_and_value(arg[j], &key, &value);
		if (catch()->error_msg != NULL)
			return ;
		if (!is_valid_key(key))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(arg[j], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			ms()->cmd[i]->cmd_status = 1;
		}
		else
			update_or_add_env_key(&ms()->env_lst, key, value);
		free_key_and_value(key, value);
		j++;
	}
	if (catch()->error_msg == NULL)
		update_ms_env();
}

void	print_export_fd(void)
{
	int		i;
	t_env	*env_lst;
	char	**env_arr;
	int		fd;

	fd = 1;
	env_lst = ms()->env_lst;
	env_arr = NULL;
	env_arr = convert_lst_to_arr(env_lst);
	if (catch()->error_msg != NULL)
		return ;
	sort_env(env_arr);
	i = 0;
	while (env_arr[i])
	{
		execute_export(fd, env_arr[i]);
		i++;
	}
	free_args(env_arr);
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

void	ft_export(int i)
{
	char	**arg;
	int		j;

	j = 1;
	arg = ms()->cmd[i]->arg;
	if (!arg[j])
		print_export_fd();
	else
		add_new_key(arg, j, i);
}
