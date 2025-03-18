/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:05:51 by joafern2          #+#    #+#             */
/*   Updated: 2025/03/17 21:14:58 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//fazer copia do ms_env para ordenar APENAS quando se printa
//ajustar print_export_fd para funcionar com a linked linked list

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
	t_env	*env_lst;
	char	**env_arr;
	int		fd;

	fd = 1;
	env_lst = ms->env_lst;
	env_arr = NULL;
	env_arr = convert_lst_to_arr(env_lst);
	sort_env(env_arr);
	i = 0;
	while (env_arr[i])
	{
		execute_export(fd, env_arr[i]);
		i++;
	}
	free_args(env_arr);
}

char	**convert_lst_to_arr(t_env *lst)
{
	char	**arr;
	char	*temp;
	int	size;
	int	i;

	temp = NULL;
	size = env_lst_size(lst);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		deallocate("Memory Allocation failed");
	i = 0;
	while (lst)
	{
		if (lst->value)
		{
			temp = ft_strjoin(lst->key, "=");
			if (!temp)
				return (NULL);
			arr[i] = ft_strjoin(temp, lst->value);
		       	free(temp);
		}
		else
			arr[i] = ft_strdup(lst->key);
		if (!arr[i])
		{
			while (i-- > 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	env_lst_size(t_env *env_lst)
{
	int	size;

	size = 0;
	while (env_lst)
	{
		size++;
		env_lst = env_lst->next;
	}
	return (size);
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
