/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/02/14 04:35:31 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	within_quotes(char *str, int *i)
{
	char	c;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		c = str[*i];
		(*i)++;
		while (str[*i] != c)
			(*i)++;
	}
}

int	check_metachar(char c) // ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, ‘>’, space, tab, newline
{
	return (c == '|' || c == '<' || c == '>' || c == '\t' || c == '\n' || c == ' ');
}

void	new_cmd(t_ms *ms)
{
	t_cmd	dummy;
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		deallocate("Error> init_cmd");
	new_cmd->arg = NULL;
	new_cmd->token = NULL;
	new_cmd->fd_in = NULL;
	new_cmd->fd_out = NULL;
	new_cmd->next = NULL;
	temp = get_last_node(ms->cmds, get_offset(&dummy, &dummy.next));
	if (temp)
		temp->next = new_cmd;
	else
		ms->cmds = new_cmd;
}

char	*new_str(char *str, int *i)
{
	int		len;
	char	*new_str;

	len = 0;
	while (str[*i + len] && !check_metachar(str[*i + len]))
	{
		if (str[*i + len] == '\"' || str[*i + len] == '\'')
			within_quotes(&str[*i + len], &len);
		else
			len++;
	}
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
	deallocate("Error> new_str");
	len = 0;
	while (str[*i] && !check_metachar(str[*i]))
	{
		new_str[len] = str[*i];
		len++;
		(*i)++;
	}
	new_str[len] = '\0';
	return (new_str);
}

void	check_quotes(char c, int *quotes)
{
	if (c == '\'' && *quotes == 1)
		*quotes = 0;
	else if (c == '\'' && *quotes == 0)
		*quotes = 1;
	else if (c == '\"' && *quotes == 2)
		*quotes = 0;
	else if (c == '\"' && *quotes == 0)
		*quotes = 2;
}

int	expansion_len(t_ms *ms, char *str, int *i)
{
	int		len;
	t_env	*temp;

	(*i)++;
	len = 0;
	if (str[*i] == '?')
		len++;
	else if (ft_isdigit(str[*i]))
		deallocate("Error> invalid identifier (envs nao podem comecar com digitos)");
	else
		while (!check_metachar(str[*i + len]))
			len++;
	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (!ft_strncmp(&str[*i], temp->key, len))
			break;
		temp = temp->next;
	}
	*i = *i + len;
	if (temp)
		return (ft_strlen(temp->value));
	return (0);
}

char	*expansion_value(t_ms *ms, char *str, int *i)
{
	int		len;
	t_env	*temp;

	len = expansion_len(ms, str, i);
	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (!ft_strncmp(&str[*i], temp->key, len))
			break;
		temp = temp->next;
	}
	if (temp)
		return (temp->value);
	return (NULL);
}

char	*expand_str(t_ms *ms, char *str)
{
	int	i;
	int	j;
	int	len;
	int	quotes;
	char	*exp;
	char	*value;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			len = len + expansion_len(ms, str, &i);
		else
		{
			i++;
			len++;
		}
	}
	exp = malloc(sizeof(char) * len + 1);
	if (!exp)
		deallocate ("Error> expand_token");
	i = 0;
	len = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
		{
			value = expansion_value(ms, str, &i);
			j = 0;
			while (value[j])
			{
				exp[len] = value[j];
				j++;
				len++;
			}
		}
		else
		{
			exp[len] = str[i];
			len++;
			i++;
		}
	}
	exp[len] = '\0';
	return (exp);
}

t_parse	*new_arg(char *str)
{
	t_parse	*new_arg;

	new_arg = malloc(sizeof(t_parse));
	if (!new_arg)
		deallocate("Error> new_arg\n");
	new_arg->token = str;
	new_arg->next = NULL;
	return (new_arg);
}

void	place_new_arg(t_ms *ms, t_parse *new_arg)
{
	t_cmd	dummy_cmd;
	t_parse	dummy_arg;
	t_cmd	*last_cmd;
	t_parse	*temp;

	last_cmd = get_last_node(ms->cmds, get_offset(&dummy_cmd, &dummy_cmd.next));
	temp = get_last_node(last_cmd->token, get_offset(&dummy_arg, &dummy_arg.next));
	if (temp)
		temp->next = new_arg;
	else
		last_cmd->token = new_arg;
}

void	token_to_array(t_cmd *cmd)
{
	int		i;
	t_parse	*temp;

	i = 0;
	temp = cmd->token;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	cmd->arg = malloc(sizeof(char *) * (i + 1));
	if (!cmd->arg)
		deallocate("Error> ll_to_array");
	temp = cmd->token;
	i = 0;
	while (temp != NULL)
	{
		cmd->arg[i] = temp->token;
		i++;
		temp = temp->next;
	}
	cmd->arg[i] = 0;
}

void	cmd_to_array(t_ms *ms)
{
	int		i;
	t_cmd	*temp_cmd;

	i = 0;
	temp_cmd = ms->cmds;
	while (temp_cmd != NULL)
	{
		i++;
		temp_cmd = temp_cmd->next;
	}
	ms->cmd = malloc(sizeof(char *) * (i + 1));
	if (!ms->cmd)
		deallocate("Error> cmd_to_array");
	temp_cmd = ms->cmds;
	i = 0;
	while (temp_cmd != NULL)
	{
		ms->cmd[i] = temp_cmd;
		token_to_array(ms->cmd[i]);
		i++;
		temp_cmd = temp_cmd->next;
	}
	ms->cmd[i] = 0;
}

void	parse_input(t_ms *ms, char *str)
{
	int		i;

	i = 0;
	while (1)
	{
		new_cmd(ms);
		while (str[i])
		{
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
			{
				i++;
				break;
			}
			// else if (str[i] == is_redirection())
			// 	redirections();
			else
				place_new_arg(ms, new_arg(expand_str(ms, new_str(str, &i))));
			//ft_printf("i: %d\n", i);
		}
		if (str[i] == '\0')
			break ;
	}
	cmd_to_array(ms);
	print_cmd(ms);
}

// void	parse_input(t_ms *ms, char *str)
// {
// 	parse_tokens(ms, str);
// 	parse_cmd(ms);
// 	print_cmd(ms);
// 	//parse_pipes(ms, str, pipe_counter(str));
// }
