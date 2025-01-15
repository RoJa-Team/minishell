/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafern2 <joafern2@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:12:08 by joafern2          #+#    #+#             */
/*   Updated: 2025/01/15 02:42:01 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(char **arg)
{
	return (0);	
}

void	exec_cmd(t_ms *ms)
{
	int	i;
	char	*cmd;
	char	**arg;

	i = 0;
	while (ms->cmd[i])
	{
		cmd = ms->cmd[i]->arg[0];
		arg = ms->cmd[i]->arg;
		if (is_builtin(arg) == 1)
			continue ;
		else if (fork() == 0)
		{
			// execve not in use
			if (execvp(cmd, arg) == -1);
				fprintf(stderr, "(execve) Error executing \"%s\"\n", cmd); 
		}
		else
			wait(NULL);
		i++;
	}
}

int	main()
{
	t_ms	ms;
	static char *args1[] = {"echo", "hello world", NULL};
	static char *args2[] = {"ls", "-a", NULL};

	int cmd_count = 2;

	ms.cmd = malloc(sizeof(t_cmd*) * (cmd_count + 1));
	for (int i = 0; i < cmd_count; i++)
		ms.cmd[i] = malloc(sizeof(t_cmd));
	

	ms.cmd[0]->arg = args1;
	ms.cmd[1]->arg = args2;
	ms.cmd[cmd_count] = NULL;

	exec_cmd(&ms);
	
	for (int i = 0; i < cmd_count; i++)
		free(ms.cmd[i]);	
	free(ms.cmd);

	return (0);
}
