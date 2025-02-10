/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:05:51 by joafern2          #+#    #+#             */
/*   Updated: 2025/02/10 18:31:27 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Key Rules for Variable Names in export:
	// Must begin with a letter or an underscore (_).
	// Can contain letters, numbers, and underscores.
	// Cannot contain special characters like /, =, \, or spaces.
	// Cannot have multiple = signs, as only the first one is used to assign a value.

void	get_key_and_value(char *arg, char **key, char **value)
{
	int	h;

	h = 0;
	*value = NULL;
	while (arg[h] && arg[h] != '=')
		h++;
	if (arg[h] == '=')
	{
		*key = ft_substr(arg, 0, h);
		*value = ft_strdup(arg + h + 1);
	}
	else
		*key = ft_strdup(arg);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_key_and_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

void	update_or_add_env_key(t_env **env, char *key, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (temp->value && value)
				free(temp->value);
			if (value)	
				temp->value = ft_strdup(value);
			else
				temp->value = NULL;
			temp->invis = 0;
			//printf("%s=%s\n", temp->key, temp->value);
			return ;
		}
		temp = temp->next;
	}
	new_node = malloc(sizeof(t_env)); 
	if (!new_node)
		deallocate("Error adding new env key\n");
	new_node->key = ft_strdup(key);
	//printf("new key is \"%s\"\n", new_node->key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	//printf("new value is \"%s\"\n", new_node->value);
	new_node->invis = 0;
	new_node->next = *env;
	*env = new_node;
}

void	swap_str(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

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
	int	i;
	char	**env;
	char	*equal;
	int	fd = 1;
	
	env = ms->ms_env;
	sort_env(env);
	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		equal = ft_strchr(env[i], '=');
	//	printf("%s\n", env[i]);
		if (equal)
		{
			write(fd, env[i], equal - env[i]);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(equal + 1, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else
		{
			ft_putstr_fd(env[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
}

int	ft_export(t_ms *ms, int i)
{
	char	**arg;
	char	*key;
	char	*value;
	int	j;
	
	j = 1;
	arg = ms->cmd[i]->arg;
	key = NULL;
	value = NULL;
	if (!arg[j])
		print_export_fd(ms);
	else
	{
		while (arg[j])
		{
			get_key_and_value(arg[j], &key, &value);
			if (!is_valid_key(key))
				ft_printf("export: %s: not a valid identifier\n", arg[j]);
			else
				update_or_add_env_key(&ms->env_lst, key, value);
			free_key_and_value(key, value);
			j++;
		}
		update_ms_env(ms);
	}
	return (1);
}
