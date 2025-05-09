/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:52:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/09 21:39:26 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_redir	*alloc_redir(int type, int operator)
{
	t_redir	*new_redir;
	t_cmd	*last_cmd;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (catch()->error_msg = "Memory allocation error: new_redir\n", \
		NULL);
	new_redir->type = type;
	new_redir->operator = operator;
	new_redir->file = NULL;
	new_redir->next = NULL;
	last_cmd = get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, \
	&dummy()->cmd.next));
	if (last_cmd->redir)
		((t_redir *)get_last_node(last_cmd->redir, get_offset(&dummy()->\
		redir, &dummy()->redir.next)))->next = new_redir;
	else
		last_cmd->redir = new_redir;
	return (new_redir);
}

void	add_redir(char *str, int *i, int type, int operator)
{
	t_redir	*new_redir;
	t_redir	*temp_redir;

	new_redir = alloc_redir(type, operator);
	if (!new_redir)
		return ;
	if (type == INPUT && operator == HEREDOC)
		new_redir->file = handle_heredoc(heredoc_quote(&str[*i]), \
			remove_quotes_heredoc(new_str(str, i)));
	else
		new_redir->file = expand_str(new_str(str, i));
	if (catch()->error_msg != NULL)
		return (temp_redir = new_redir, temp_redir = NULL, \
		free(temp_redir), (void) NULL);
	if (!new_redir->file)
		return (temp_redir = new_redir, temp_redir = NULL, \
		free(new_redir), catch()->error_msg = \
		"Memory allocation error: ft_itoa\n", (void) NULL);
}

void	new_redir(char *str, int *i)
{
	int		len;
	char	redir;

	len = 0;
	redir = str[*i];
	while (str[*i] && str[*i] == str[*i + len])
		len++;
	*i = *i + len;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (len == 2 && redir == '<')
		add_redir(str, i, INPUT, HEREDOC);
	else if (len == 2 && redir == '>')
		add_redir(str, i, OUTPUT, APPEND);
	else if (len == 1 && redir == '<')
		add_redir(str, i, INPUT, IN);
	else if (len == 1 && redir == '>')
		add_redir(str, i, OUTPUT, OUT);
}
