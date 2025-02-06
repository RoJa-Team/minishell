/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/06 20:13:47 by rafasant         ###   ########.fr       */
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

t_parse	*new_token(char *str, int len, char c)
{
	t_parse	*token;

	token = malloc(sizeof(t_parse));
	if (!token)
		deallocate("Error> new_token");
	token->token = ft_strndup(str, len);
	token->quotes = 0;
	if (c == '\'')
		token->quotes = 1;
	else if (c == '\"')
		token->quotes = 2;
	token->next = NULL;
	return (token);
}

void	insert_new_token(t_ms *ms, t_parse *new_token)
{
	t_parse	*temp;

	if (!ms->parse)
		ms->parse = new_token;
	else
	{
		temp = ms->parse;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
	}
}

void	parse_tokens(t_ms *ms, char *str) // simplified version, needs to be more specific - handle quotes and redirections
{
	int		i;
	int		len;
	char	c;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		len = 0;
		while (str[i + len] && str[i + len] != ' ')
		{
			if (str[i + len] == '\"' || str[i + len] == '\'')
			{
				c = str[i + len];
				len++;
				while (str[i + len] != c)
					len++;
			}
			len++;
		}
		insert_new_token(ms, new_token(&str[i], len, c));
		i = i + len;
	}
	// char	**tokensv1;
	// t_parse	*temp;

	// tokensv1 = ft_split(str, ' ');
	// if (!tokensv1)
	// 	deallocate("Error> split tokensv1");
	// int	i = 0;
	// while (tokensv1[i] != NULL)
	// {
	// 	if (!ms->parse)
	// 		ms->parse = new_token(tokensv1[i]);
	// 	else
	// 	{
	// 		temp = ms->parse;
	// 		while (temp->next != NULL)
	// 			temp = temp->next;
	// 		temp->next = new_token(tokensv1[i]);
	// 	}
	// 	i++;
	// }
	// free_array(tokensv1);
}

char	*expand_token(t_ms *ms, t_parse *token)
{
	int		i;
	int		len;
	int		new_len;
	int		total;
	char	*exp;
	t_env	*temp;

	i = 0;
	new_len = ft_strlen(token->token);
	while (token->token[i])
	{
		if (token->token[i] == '$' && (token->quotes == 2 || token->quotes == 0))
		{
			len = 0;
			i++;
			while (ft_isalnum(token->token[i + len]))
				len++;
			temp = ms->env_lst;
			while (temp != NULL)
			{
				if (!ft_strncmp(&token->token[i], temp->key, len))
					break;
				temp = temp->next;
			}
			if (temp)
				new_len = new_len + ft_strlen(temp->value) - (len + 1);
			else
				new_len = new_len - len;
			i = i + len;
		}
		else
			i++;
	}
	exp = malloc(sizeof(char) * new_len + 1);
	if (!exp)
		deallocate ("Error> expand_token");
	i = 0;
	total = 0;
	int	j;
	while (token->token[i])
	{
		if (token->token[i] == '$' && (token->quotes == 2 || token->quotes == 0))
		{
			len = 0;
			i++;
			while (ft_isalnum(token->token[i + len]))
				len++;
			temp = ms->env_lst;
			while (temp != NULL)
			{
				if (!ft_strncmp(&token->token[i], temp->key, len))
					break;
				temp = temp->next;
			}
			j = 0;
			while (temp && temp->value[j])
			{
				exp[total] = temp->value[j];
				j++;
				total++;
			}
			i = i + len;
		}
		else
		{
			exp[total] = token->token[i];
			total++;
			i++;
		}
	}
	exp[total] = '\0';
	return (exp);
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
	ms->cmd[0]->arg = malloc(sizeof(char *) * (i + 1));
	if (!ms->cmd[0]->arg)
		deallocate("Error> new_cmd");
	temp = ms->parse;
	i = 0;
	while (temp != NULL)
	{
		ms->cmd[0]->arg[i] = expand_token(ms, temp);
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
	print_cmd(ms);
	//parse_pipes(ms, str, pipe_counter(str));
}