/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:52:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/05/07 15:53:23 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	add_redir(char *file, int type, int operator)
{
	t_redir	*new_redir;
	t_cmd	*last_cmd;

	if (!file)
		return (catch()->error_msg = "Memory allocation error: new_redir\n", \
		(void) NULL);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (catch()->error_msg = "Memory allocation error: new_redir\n", \
		(void) NULL);
	new_redir->type = type;
	new_redir->operator = operator;
	new_redir->file = file;
	new_redir->next = NULL;
	last_cmd = get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, \
	&dummy()->cmd.next));
	if (last_cmd->redir)
		((t_redir *)get_last_node(last_cmd->redir, get_offset(&dummy()->\
		redir, &dummy()->redir.next)))->next = new_redir;
	else
		last_cmd->redir = new_redir;
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
		add_redir(ft_itoa(handle_heredoc(heredoc_quote(&str[*i]), \
		get_del(str, i, 0, 0))), INPUT, HEREDOC);
	else if (len == 2 && redir == '>')
		add_redir(get_file(str, i, 0, 0), OUTPUT, APPEND);
	else if (len == 1 && redir == '<')
		add_redir(get_file(str, i, 0, 0), INPUT, IN);
	else if (len == 1 && redir == '>')
		add_redir(get_file(str, i, 0, 0), OUTPUT, OUT);
}
