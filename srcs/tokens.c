// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tokens.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/10 21:11:57 by rafasant          #+#    #+#             */
// /*   Updated: 2025/02/14 01:28:14 by rafasant         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../headers/minishell.h"

// void	insert_new_token(t_ms *ms, t_parse *new_token)
// {
// 	t_parse	*temp;

// 	if (!ms->parse)
// 		ms->parse = new_token;
// 	else
// 	{
// 		temp = ms->parse;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new_token;
// 	}
// }

// t_parse	*new_token(char *str, int len)
// {
// 	t_parse	*token;

// 	token = malloc(sizeof(t_parse));
// 	if (!token)
// 		deallocate("Error> new_token");
// 	token->token = ft_strndup(str, len);
// 	token->next = NULL;
// 	return (token);
// }

// void	within_quotes(char *str, int *i)
// {
// 	int		len;
// 	char	c;

// 	len = *i;
// 	if (str[len] == '\"' || str[len] == '\'')
// 	{
// 		c = str[len];
// 		len++;
// 		while (str[len] != c)
// 			len++;
// 	}
// 	*i = len;
// }

// int	check_metachar(char c) // ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, ‘>’, space, tab, newline
// {
// 	return (c == '|' || c == '<' || c == '>' || c == '\t' || c == '\n' || c == ' ');
// }

// void	parse_tokens(t_ms *ms, char *str) // echo o"la $PWD b"ac'oac$OLDPWDbc'ol
// {
// 	int		i;
// 	int		len;
// 	char	c;

// 	i = 0;
// 	while (str[i])
// 	{
// 		while (ft_isspace(str[i]))
// 			i++;
// 		len = 0;
// 		while (str[i + len] && str[i + len] != ' ') // !check_metachar(str[i + len])
// 		{
// 			if (str[i + len] == '\"' || str[i + len] == '\'')
// 				within_quotes(&str[i], &len);
// 			else if (str[i + len] == '<' || str[i + len] == '>')// not finished echo 123 >>> doesnt give error for example
// 			{
// 				if (str[len] == '\"' || str[len] == '\'')
// 					within_quotes(&str[i], &len);
// 				if (str[i + len + 1] == ' ')
// 					len++;
// 				else if (str[i + len + 2] == ' ')
// 					len = len + 2;
// 				while (str[i + len] != '\0' && ft_isspace(str[i + len]))
// 					len++;
// 				while (str[i + len] != '\0' && !ft_isspace(str[i + len]))
// 					len++;
// 				len--;
// 			}
// 			len++;
// 		}
// 		if (len != 0)
// 			insert_new_token(ms, new_token(&str[i], len));
// 		i = i + len;
// 	}
// }

// void	check_quotes(char c, int *quotes)
// {
// 	if (c == '\'' && *quotes == 1)
// 		*quotes = 0;
// 	else if (c == '\'' && *quotes == 0)
// 		*quotes = 1;
// 	else if (c == '\"' && *quotes == 2)
// 		*quotes = 0;
// 	else if (c == '\"' && *quotes == 0)
// 		*quotes = 2;
// }

// void	expansion_len(t_ms *ms, t_parse *token, int *ptr, int *new_len)
// {
// 	int		len;
// 	int		i;
// 	t_env	*temp;

// 	len = 0;
// 	i = *ptr;
// 	i++;
// 	while (ft_isalnum(token->token[i + len]))
// 		len++;
// 	temp = ms->env_lst;
// 	while (temp != NULL)
// 	{
// 		if (!ft_strncmp(&token->token[i], temp->key, len))
// 			break;
// 		temp = temp->next;
// 	}
// 	if (temp)
// 		*new_len = *new_len + ft_strlen(temp->value) - (len + 1);
// 	else
// 		*new_len = *new_len - len;
// 	i = i + len;
// 	*ptr = i;
// }

// // void	expansion_str(t_ms *ms, t_parse *token, char **exp)
// // {
// // 	int		i;
// // 	int		j;
// // 	int		len;
// // 	int		total;
// // 	int		quotes;
// // 	t_env	*temp;

// // 	while (token->token[i])
// // 	{
// // 		check_quotes(token->token[i], &quotes);
// // 		if (token->token[i] == '$' && (quotes == 2 || quotes == 0))
// // 		{
// // 			len = 0;
// // 			i++;
// // 			while (ft_isalnum(token->token[i + len]))
// // 				len++;
// // 			temp = ms->env_lst;
// // 			while (temp != NULL)
// // 			{
// // 				if (!ft_strncmp(&token->token[i], temp->key, len))
// // 					break;
// // 				temp = temp->next;
// // 			}
// // 			j = 0;
// // 			while (temp && temp->value[j])
// // 			{
// // 				*exp[total] = temp->value[j];
// // 				j++;
// // 				total++;
// // 			}
// // 			i = i + len;
// // 		}
// // 		else
// // 		{
// // 			*exp[total] = token->token[i];
// // 			total++;
// // 			i++;
// // 		}
// // 	}
// // 	*exp[total] = '\0';
// // 	return (*exp);
// // }

// void	new_redir(t_ms *ms, char *file, int type)
// {
// 	int		i;
// 	t_redir	*new_redir;
// 	t_redir	*temp;

// 	i = 0;
// 	// while (ms->cmd[i] && ms->cmd[i + 1])
// 	// 	i++;
// 	temp = ms->cmd[i]->fd_in;
// 	ft_printf("file: %s\n", file);
// 	new_redir = malloc(sizeof(t_redir));
// 	if (!new_redir)
// 		deallocate("Error> new_redir");
// 	new_redir->type = type;
// 	new_redir->file = file;
// 	new_redir->next = NULL;
// 	if (!temp)
// 		temp = new_redir;
// 	else
// 		while (temp && temp->next)
// 			temp = temp->next;
// }

// char	*get_file(t_parse *token, int *ptr, int *new_len, int type)
// {
// 	int		i;
// 	int		len;
// 	char	*file;

// 	i = *ptr;
// 	i = i + type;
// 	if (token->token[i] == '\0')
// 		deallocate("Error> get_file\n");
// 	while (ft_isspace(token->token[i]))
// 		i++;
// 	len = 0;
// 	while (token->token[i + len] && !ft_isspace(token->token[i + len]))
// 		len++;
// 	file = malloc(sizeof(char) * len + 1);
// 	if (!file)
// 		deallocate("Error> malloc get_file\n");
// 	len = 0;
// 	while (token->token[i + len] && !ft_isspace(token->token[i + len]))
// 	{
// 		file[len] = token->token[i + len];
// 		len++;
// 	}
// 	file[len] = '\0';
// 	*ptr = i + len;
// 	*new_len = *new_len - type - len;
// 	return (file);
// }

// void	redirections(t_ms *ms, t_parse *token, int *ptr, int *new_len)
// {
// 	if (token->token[*ptr] == token->token[*ptr + 1] && token->token[*ptr] == '<')
// 		ft_printf("Isto seria um heredoc!\n");
// 	else if (token->token[*ptr] == token->token[*ptr + 1] && token->token[*ptr] == '>')
// 		new_redir(ms, get_file(token, ptr, new_len, APPEND), APPEND);
// 	else if (token->token[*ptr] == '<' && token->token[*ptr + 1] != '>')
// 		new_redir(ms, get_file(token, ptr, new_len, IN), IN);
// 	else if (token->token[*ptr] == '>' && token->token[*ptr + 1] != '<')
// 		new_redir(ms, get_file(token, ptr, new_len, OUT), OUT);
// 	else
// 		return ((void)ft_printf("Error> Invalid redirection"));
// }

// char	*expand_token(t_ms *ms, t_parse *token)
// {
// 	int		i;
// 	int		len;
// 	int		new_len;
// 	int		total;
// 	int		quotes;
// 	char	*exp;
// 	t_env	*temp;

// 	i = 0;
// 	new_len = ft_strlen(token->token);
// 	quotes = 0;
// 	while (token->token[i])
// 	{
// 		check_quotes(token->token[i], &quotes);
// 		if (token->token[i] == '$' && (quotes == 2 || quotes == 0))
// 			expansion_len(ms, token, &i, &new_len);
// 		else if ((token->token[i] == '<' || token->token[i] == '>') && quotes == 0)
// 			redirections(ms, token, &i, &new_len);
// 		else
// 			i++;
// 	}
// 	ft_printf("new_len: %d\n", new_len);
// 	exp = malloc(sizeof(char) * new_len + 1);
// 	if (!exp)
// 		deallocate ("Error> expand_token");
// 	i = 0;
// 	total = 0;
// 	int	j;
// 	while (token->token[i])
// 	{
// 		check_quotes(token->token[i], &quotes);
// 		if (token->token[i] == '$' && (quotes == 2 || quotes == 0))
// 		{
// 			len = 0;
// 			i++;
// 			while (ft_isalnum(token->token[i + len]))
// 				len++;
// 			temp = ms->env_lst;
// 			while (temp != NULL)
// 			{
// 				if (!ft_strncmp(&token->token[i], temp->key, len))
// 					break;
// 				temp = temp->next;
// 			}
// 			j = 0;
// 			while (temp && temp->value[j])
// 			{
// 				exp[total] = temp->value[j];
// 				j++;
// 				total++;
// 			}
// 			i = i + len;
// 		}
// 		else
// 		{
// 			exp[total] = token->token[i];
// 			total++;
// 			i++;
// 		}
// 	}
// 	exp[total] = '\0';
// 	return (exp);
// }