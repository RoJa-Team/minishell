/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:37:16 by joafern2          #+#    #+#             */
/*   Updated: 2025/04/07 21:23:58 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	assign_to_ms_env()
{
	t_env	*temp2;
	char	*temp3;
	int		i;

	i = 0;
	temp2 = ms()->env_lst;
	while (temp2 != NULL)
	{
		if (!temp2->invis)
		{
			if (temp2->value)
			{
				temp3 = ft_strjoin(temp2->key, "=");
				ms()->ms_env[i] = ft_strjoin(temp3, temp2->value);
				free(temp3);
			}
			else
				ms()->ms_env[i] = ft_strdup(temp2->key);
			i++;
		}
		temp2 = temp2->next;
	}
	ms()->ms_env[i] = NULL;
}

char	*print_oldpwd(t_env *env)
{
	t_env	*temp;
	char	*value;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 7) == 0)
		{
			value = check_visibility(temp);
			if (!value)
				break ;
			else
				return (value);
		}
		temp = temp->next;
	}
	ft_printf("cd: OLDPWD not set\n");
	ms()->exit_status = 1;
	return (NULL);
}

char	*check_visibility(t_env *temp)
{
	char	*value;

	if (temp->invis == 0)
	{
		ft_putstr_fd(temp->value, 1);
		ft_putchar_fd('\n', 1);
		value = ft_strdup(temp->value);
		if (!value)
			deallocate("memory allocation fail.\n");
		return (value);
	}
	else
		return (NULL);
}

void	ft_cd(int i)
{
	t_env	*temp;
	char	*oldpwd;
	char	*newpwd;
	char	**arg;
	int		count;

	arg = ms()->cmd[i]->arg;
	count = arg_count(arg);
	if (count > 2)
	{
		ft_printf("cd: too many arguments\n");
		ms()->exit_status = 1;
		return ;
	}
	temp = ms()->env_lst;
	newpwd = NULL;
	oldpwd = get_value(temp, "PWD");
	if (count < 2)
		newpwd = get_home(temp);
	else
		newpwd = get_ab_path(oldpwd, arg[1]);
	if (!newpwd)
		return ;
	change_directory(oldpwd, newpwd, i);
}

void	change_directory(char *oldpwd, char *newpwd, int i)
{
	t_env		*temp;

	temp = ms()->env_lst;
	if (newpwd && chdir(newpwd) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", ms()->cmd[i]->arg[1]);
		ms()->exit_status = 1;
	}
	else if (newpwd)
	{
		update_env_lst(temp, "OLDPWD", oldpwd);
		update_env_lst(temp, "PWD", newpwd);
		update_ms_env();
		ms()->exit_status = 0;
	}
	if (oldpwd)
		free(oldpwd);
	if (newpwd)
		free(newpwd);
}
