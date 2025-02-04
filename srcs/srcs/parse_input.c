/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/30 05:01:09 by joafern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	pipe_counter(char *str)
{
	int	pipes;
	int	quote;

	if (!str)
		return 0;

	pipes = 0;
	quote = 0;
	while(*str)
	{ 
		if (*str == '"' && quote == 1)
			quote = 0;
		else if (*str == '"')
			quote = 1;
		if (*str == '|' && quote == 0)
			pipes++;
		str++;
	}
	if (quote == 1)
		deallocate("Error> invalid number of quotes.\n");
	return (pipes);
}

// void	quote_validator(char *str)
// {
// 	int	quote;

// 	quote = 0;
// 	while(*str)
// 	{
// 		if (*str == '"' && quote == 1)
// 			quote = 0;
// 		else if (*str == '"')
// 			quote = 1;
// 		str++;
// 	}
// 	if (quote == 1)
// 		deallocate("Error> invalid number of quotes.\n");
// }

// void	redirections(t_ms *ms, char *cmd, int n_cmd)
// {
// 	ms->cmd[n_cmd]->fd_in = NULL;
// 	ms->cmd[n_cmd]->fd_out = NULL;
// 	ms->cmd[n_cmd]->append = 0;

// 	while (*cmd)
// 	{
// 		if (*cmd == '>' && *(cmd + 1) == '>')
// 		{
// 			ms->cmd[n_cmd]->append = 1;
// 		}
// 		else if (*cmd == '<' && *(cmd + 1) == '<')
// 		{
			
// 		}
// 		else if (*cmd == '>')
// 			;
// 		else if (*cmd == '<')
// 			;
// 		cmd++;
// 	}
// }

// void	parse_pipes(t_ms *ms, char *str, int pipes)
// {
// 	int		i;
// 	char	**cmds;

// 	cmds = ft_split(str, '|');
// 	i = 0;
// 	if (!cmds)
// 		return;
// 	while (cmds[i] != 0)
// 		i++;
// 	if (i != pipes + 1)
// 		deallocate("Error> invalid pipes.");
// 	ms->cmd = malloc(sizeof(t_cmd *) * (i + 1));
// 	if (!ms->cmd)
// 		deallocate("Error> invalid pipes.");
// 	i = 0;
// 	while (cmds != 0 && i != pipes + 1)
// 	{
// 		ms->cmd[i] = malloc(sizeof(t_cmd));
// 		if (!ms->cmd[i])
// 			deallocate("Error> parse_pipes");
// 		ms->cmd[i]->arg = ft_split(cmds[i], ' ');
// 		// redirections(ms, cmds[i], i);
// 		i++;
// 	}
// 	ms->cmd[i] = NULL;
// }

t_parse	*new_token(char *str)
{
	t_parse	*token;

	token = malloc(sizeof(t_parse));
	if (!token)
		deallocate("Error> new_token");
	token->token = ft_strdup(str);
	token->quotes = 0;
	token->next = NULL;
	return (token);
}

void	parse_tokens(t_ms *ms, char *str) // simplified version, needs to be more specific - handle quotes and redirections
{
	char	**tokensv1;
	t_parse	*temp;

	tokensv1 = ft_split(str, ' ');
	if (!tokensv1)
		deallocate("Error> split tokensv1");
	int	i = 0;
	while (tokensv1[i] != NULL)
	{
		if (!ms->parse)
			ms->parse = new_token(tokensv1[i]);
		else
		{
			temp = ms->parse;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_token(tokensv1[i]);
		}
		i++;
	}
	//free_array(tokensv1);
}

void	new_cmd(t_ms *ms)
{
	int	i = 0;
	t_parse	*temp;

	ms->cmd[0] = malloc(sizeof(t_cmd));
	if (!ms->cmd[0])
		deallocate("Error> new_cmd");
	temp = ms->parse;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
//	ft_printf("i: %d\n", i);
	ms->cmd[0]->arg = malloc(sizeof(t_arg *) * (i + 1));
	if (!ms->cmd[0]->arg)
		deallocate("Error> new_cmd");
	temp = ms->parse;
	i = 0;
	while (temp != NULL)
	{
		ms->cmd[0]->arg[i] = malloc(sizeof(t_arg));
		if (!ms->cmd[0]->arg[i])
			deallocate("Error> new_cmd");
		ms->cmd[0]->arg[i]->str = ft_strdup(temp->token);
		ms->cmd[0]->arg[i]->env_key = NULL;
		temp = temp->next;
		i++;
	}
	ms->cmd[0]->arg[i] = NULL;
}

void	parse_cmd(t_ms *ms)
{
	ms->cmd = malloc(sizeof(t_cmd *) * (0 + 2)); //substituir 0 por número de pipes
	if (!ms->cmd)
		deallocate("Error> parse_cmd");
	new_cmd(ms);
	ms->cmd[1] = NULL;
	// int		pipes;
	// t_parse	*temp;

	// pipes = 0;
	// temp = ms->parse;
	// while (temp != NULL)
	// {
	// 	if (temp->token == ft_strcmp("|"))
	// 		pipes++;
	// 	temp = temp->next;
	// }
	// ms->cmd = malloc(sizeof(t_cmd *) * (pipes + 2));
	// if (!ms->cmd)
	// 	deallocate("Error> parse_cmd");
	// ms->cmd[pipes + 1] = NULL;
	// while (pipes >= 0)
	// {
		
	// 	pipes--;
	// }
	// ms->cmd[pipes] = new_cmd(ms);
}

void	parse_input(t_ms *ms, char *str)
{
	parse_tokens(ms, str);
	parse_cmd(ms);
	//parse_pipes(ms, str, pipe_counter(str));
	int	i = 0;
	while (ms->cmd[i])
	{
		int	j = 0;
		while (ms->cmd[i]->arg[j])
		{
//			ft_printf("%d.%d> %s\n", i, j, ms->cmd[i]->arg[j]->str);
			j++;
		}
		i++;
	}
}
