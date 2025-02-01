/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:12:08 by joafern2          #+#    #+#             */
/*   Updated: 2025/02/01 02:55:43 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(t_ms *ms, int i)
{
	t_arg **arg;

	arg = ms->cmd[i]->arg;
	if (ft_strncmp(arg[0]->str, "echo", 5) == 0)
		return (ft_echo(ms, i));
	else if (ft_strncmp(arg[0]->str, "cd", 2) == 0)
		return (ft_cd(ms, i));
	/*
	else if (arg[0] == "pwd")
		ft_pwd(ms);
	else if (arg[0] == "export")
		ft_export(ms);
	else if (arg[0] == "unset")
		ft_unset(ms);
	else if (arg[0] == "env")
		ft_env(ms);
	else if (arg[0] == "exit")
		ft_exit(ms);
	*/
	return (0);	
}

char	*get_value(t_env *env, char *key)
{
	t_env	*temp;
	char	*value;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			if (temp->invis == 0)
			{
				value = ft_strdup(temp->value);
				if (!value)
					return(NULL);
			       	else
					return (value);
			}
			else
				return (NULL);
		}
		temp = temp->next;
	}
	return (NULL);
}
// TBC add ft_getenv ; add t_env to check for visibility
char	*find_path(t_env *env_lst, char *cmd)
{
	char	*path_env;
	char	**path_dir;
	char	*full_path;
	char	*temp;
	int	i;

	(void)env_lst;
	i = 0;
	path_env = get_value(env_lst, "PATH"); // using my_env
	if (!path_env)
		return (NULL);
	path_dir = ft_split(path_env, ':');
	if (!path_dir)
		deallocate("Failed to split $PATH\n");
	while (path_dir[i])
	{
		temp = ft_strjoin(path_dir[i], "/");
		full_path = ft_strjoin(temp, cmd);
		if (!full_path)
			deallocate("Failed to join command to $PATH\n");
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(temp);
		free(full_path);
		free(path_dir[i]);
		i++;
	}
	free(path_dir);
	return (NULL);
}

int	node_count(t_arg **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	exec_cmd(t_ms *ms)
{
	int	i;
	char	*cmd;
	char	**arg;
	char	*path;

	i = 0;
	while (ms->cmd[i])
	{
		cmd = ms->cmd[i]->arg[0]->str;
		if (is_builtin(ms, i) == 1)
		{
			i++;
			continue ;
		}
		else if (fork() == 0)
		{
			arg = convert_args_to_char(ms, i);
			path = find_path(ms->env_lst, cmd);
			if (!path)
			{
				printf("%s: command not found\n", arg[0]);
				return ;
			}
			if (execve(path, arg, ms->ms_env) == -1) // my_env in use
			{
				deallocate("Error executing execve.\n");
				free(path);
			}
			free(path);
			free(arg);
		}
		else
		{
			// check for herededoc
			wait(NULL);
		}
		i++;
	}
}

char	**convert_args_to_char(t_ms *ms, int h)
{
	int	j;
	int	i;
	int	count;
	char	**result;

	i = 0;
	count = 0;
	while (ms->cmd[h]->arg[i])
	{
		if (ms->cmd[h]->arg[i]->str)
			count++;
		i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (ms->cmd[h]->arg[i])
	{
		if (ms->cmd[h]->arg[i]->str)
		{
			result[j] = ft_strdup(ms->cmd[h]->arg[i]->str);
			j++;
		}
		else if (ft_strncmp(ms->cmd[h]->arg[i]->env_key, "OLDPWD", 6) == 0)
		{
			result[j] = get_value(ms->env_lst, "OLDPWD");
			j++;
		}
		i++;
	}
	//printf ("%d\n", j);
	result[j] = NULL;
	return (result);
}

/*
int	main()
{
	t_ms	ms;
	//static char *args1[] = {"grep", "-E", "c$", "-", NULL};
	static char *args2[] = {"echo", "hello", NULL, "world", NULL};

	int cmd_count = 1;

	ms.cmd = malloc(sizeof(t_cmd*) * (cmd_count + 1));
	for (int i = 0; i < cmd_count; i++)
	{
		int	k;
		int	j = 5;
		ms.cmd[i] = malloc(sizeof(t_cmd));
		//for (j = 0; args2[j]; j++)
		//	;
		ms.cmd[i]->arg = malloc(sizeof(t_arg*) * (j + 1));
		for (k = 0; k < j - 1; k++)
		{
			if (args2[k])
			{
				ms.cmd[i]->arg[k] = malloc(sizeof(t_arg));
				ms.cmd[i]->arg[k]->str = ft_strdup(args2[k]);
				ms.cmd[i]->arg[k]->env_key = NULL;
			}
			else
			{
				ms.cmd[i]->arg[k] = malloc(sizeof(t_arg));
				ms.cmd[i]->arg[k]->str = NULL;
				ms.cmd[i]->arg[k]->env_key = NULL;
			}
		}
		ms.cmd[i]->arg[k] = NULL;
	}
	ms.cmd[cmd_count] = NULL;

	exec_cmd(&ms);
	
	for (int i = 0; i < cmd_count; i++)
	{
		for (int j = 0; ms.cmd[i]->arg[j]; j++)
		{
			if (ms.cmd[i]->arg[j]->str)
			{
				free(ms.cmd[i]->arg[j]->str);
			}
			free(ms.cmd[i]->arg[j]);
		}
		free(ms.cmd[i]->arg);
		free(ms.cmd[i]);
	}	
	free(ms.cmd);
	return (0);
}*/
