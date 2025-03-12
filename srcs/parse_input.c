/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/12 21:02:05 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	within_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	i++;
	while (str[i] != c)
		i++;
	i++;
	return (i);
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
	temp = NULL;
	if (ms->cmds)
		temp = get_last_node(ms->cmds, get_offset(&dummy, &dummy.next));
	if (temp)
		temp->next = new_cmd;
	else
		ms->cmds = new_cmd;
}

char	*new_str(char *str, int *i)
{
	int		j;
	int		len;
	char	*new_str;

	len = 0;
	while (str[*i + len] && !check_metachar(str[*i + len]))
	{
		if (str[*i + len] == '\"' || str[*i + len] == '\'')
			len = len + within_quotes(&str[*i + len]);
		else
			len++;
	}
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
	deallocate("Error> new_str");
	j = 0;
	while (j < len)
	{
		new_str[j] = str[*i];
		j++;
		(*i)++;
	}
	new_str[j] = '\0';
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
		while (str[*i + len] && !check_metachar(str[*i + len]) && str[*i + len] != '\'' && str[*i + len] != '\"')
			len++;
	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (ft_strlen_c(&str[*i], str[*i + len]) == ft_strlen(temp->key) && !strncmp(&str[*i], temp->key, len))
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

	(*i)++;
	len = 0;
	while (str[*i + len] && !check_metachar(str[*i + len]) && str[*i + len] != '\'' && str[*i + len] != '\"')
		len++;
	temp = ms->env_lst;
	while (temp != NULL)
	{
		if (ft_strlen_c(&str[*i], str[*i + len]) == ft_strlen(temp->key) && !strncmp(&str[*i], temp->key, len))
			break;
		temp = temp->next;
	}
	*i = *i + len;
	if (temp)
		return (temp->value);
	return (NULL);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	exp_len(t_ms *ms, char *str)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	check_quotes(str[i], &quotes);
	while (str[i])
	{
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
			len = len + expansion_len(ms, str, &i);
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
				len++;
			i++;
		}
		check_quotes(str[i], &quotes);
	}
	return (len);
}

char	*expand_str(t_ms *ms, char *str)
{
	int	i;
	int	j;
	int	len;
	int	quotes;
	char	*exp;
	char	*value;

	exp = malloc(sizeof(char) * exp_len(ms, str) + 1);
	if (!exp)
		deallocate ("Error> expand_token");
	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		check_quotes(str[i], &quotes);
		if (str[i] == '$' && (quotes == 2 || quotes == 0))
		{
			value = expansion_value(ms, str, &i);
			j = 0;
			while (value && value[j])
			{
				exp[len] = value[j];
				j++;
				len++;
			}
		}
		else
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				exp[len] = str[i];
				len++;
			}
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



char	*get_file(t_parse *token, int *ptr, int *new_len, int type)
{
	int		i;
	int		len;
	char	*file;

	i = *ptr;
	i = i + type;
	if (token->token[i] == '\0')
		deallocate("Error> get_file\n");
	while (ft_isspace(token->token[i]))
		i++;
	len = 0;
	while (token->token[i + len] && !ft_isspace(token->token[i + len]))
		len++;
	file = malloc(sizeof(char) * len + 1);
	if (!file)
		deallocate("Error> malloc get_file\n");
	len = 0;
	while (token->token[i + len] && !ft_isspace(token->token[i + len]))
	{
		file[len] = token->token[i + len];
		len++;
	}
	file[len] = '\0';
	*ptr = i + len;
	*new_len = *new_len - type - len;
	return (file);
}

void	new_input(t_ms *ms, char *file, int type)
{
	t_cmd	cmd_dummy;
	t_cmd	*last_cmd;
	t_redir	redir_dummy;
	t_redir	*new_redir;
	t_redir	*temp;

	last_cmd = get_last_node(ms->cmd, get_offset(&cmd_dummy, &cmd_dummy.next));
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Error> new_redir");
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	temp = NULL;
	if (last_cmd->fd_in)
	{
		temp = get_last_node(last_cmd->fd_in, get_offset(&redir_dummy, &redir_dummy.next));
		temp->next = new_redir;
	}
	else
		last_cmd->fd_in = new_redir;
}

void	new_output(t_ms *ms, char *file, int type)
{
	t_cmd	cmd_dummy;
	t_cmd	*last_cmd;
	t_redir	redir_dummy;
	t_redir	*new_redir;
	t_redir	*temp;

	last_cmd = get_last_node(ms->cmd, get_offset(&cmd_dummy, &cmd_dummy.next));
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Error> new_redir");
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	temp = NULL;
	if (last_cmd->fd_out)
	{
		temp = get_last_node(last_cmd->fd_out, get_offset(&redir_dummy, &redir_dummy.next));
		temp->next = new_redir;
	}
	else
		last_cmd->fd_out = new_redir;
}

// void	redirections(t_ms *ms, char *str, int *i)
// {
// 	if (str[*i + 1] == '|' || (str[*i] == str[*i + 1] && str[*i + 2] == '|'))
// 		return ("Error> Invalid redirection");
// 	if (str[*i] == str[*i + 1] && str[*i] == '<')
// 		ft_printf("Isto seria um heredoc!\n");
// 	else if (str[*i] == str[*i + 1] && str[*i] == '>')
// 		new_output(ms, get_file(token, i, new_len, APPEND), APPEND);
// 	else if (str[*i] == '<' && str[*i + 1] != '>')
// 		new_input(ms, get_file(token, i, new_len, IN), IN);
// 	else if (str[*i] == '>' && str[*i + 1] != '<')
// 		new_output(ms, get_file(token, i, new_len, OUT), OUT);
// 	else if (str[*i] == str[*i + 1])
// 		return ((void)ft_printf("Error> Invalid redirection"));
// }

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
			// else if (str[i] == '<' || str[i] == '>')
			// 	redirections(ms, str, &i);
			else
				place_new_arg(ms, new_arg(expand_str(ms, new_str(str, &i))));
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
