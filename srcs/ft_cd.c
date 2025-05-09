/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:37:16 by joafern2          #+#    #+#             */
/*   Updated: 2025/05/09 21:57:52 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	assign_to_ms_env(void)
{
	t_env	*temp2;
	char	*temp3;
	int		i;

	i = 0;
	temp2 = ms()->env_lst;
	temp3 = NULL;
	while (temp2 != NULL && catch()->error_msg == NULL)
	{
		if (!temp2->invis)
		{
			assign_visible(temp2, temp3, &i);
			i++;
		}
		temp2 = temp2->next;
	}
	ms()->ms_env[i] = NULL;
}

void	assign_visible(t_env *temp2, char *temp3, int *i)
{
	if (temp2->value)
	{
		temp3 = ft_strjoin(temp2->key, "=");
		if (!temp3)
			return ((void)(catch()->error_msg = "Strjoin failed"));
		(ms()->ms_env[*i]) = ft_strjoin(temp3, temp2->value);
		if (!ms()->ms_env[*i])
			return ((void)(catch()->error_msg = "Strjoin failed"));
		free(temp3);
	}
	else
	{
		ms()->ms_env[*i] = ft_strdup(temp2->key);
		if (!ms()->ms_env[*i])
			return ((void)(catch()->error_msg = "Strdup failed"));
	}
}

void	ft_cd(int i)
{
	t_env	*temp;
	char	*oldpwd;
	char	*newpwd;
	int		count;

	if (i > 0 || ms()->cmd[i + 1])
		return ;
	count = arg_count(ms()->cmd[i]->arg);
	if (count > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		ms()->cmd[i]->cmd_status = 1;
		return ;
	}
	temp = ms()->env_lst;
	newpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = check_pwd(NULL);
	if (count < 2)
		newpwd = get_home(temp, ms()->cmd[i]);
	else
		newpwd = get_ab_path(ft_strdup(oldpwd), ms()->cmd[i]->arg[1]);
	if (newpwd && catch()->error_msg == NULL)
		change_directory(oldpwd, newpwd, i);
}

void	change_directory(char *oldpwd, char *newpwd, int i)
{
	t_env	*temp;

	temp = ms()->env_lst;
	if (newpwd && chdir(newpwd) != 0)
		newpwd = cd_no_file(oldpwd, newpwd, i);
	else if (newpwd && catch()->error_msg == NULL)
	{
		update_env_lst(temp, "OLDPWD", oldpwd);
		update_env_lst(temp, "PWD", newpwd);
		update_ms_env();
	}
	if (ms()->exec->pwd == oldpwd)
		free(ms()->exec->pwd);
	else
	{
		free(oldpwd);
		free(ms()->exec->pwd);
	}
	ms()->exec->pwd = newpwd;
}
