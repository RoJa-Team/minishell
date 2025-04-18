/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:52:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/18 19:09:16 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	new_input(char *file, int type)
{
	t_redir	*new_redir;
	t_cmd	*last_cmd;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Memory allocation error: new_redir\n");
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	last_cmd = get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, \
	&dummy()->cmd.next));
	if (last_cmd->fd_in)
		((t_redir *)get_last_node(last_cmd->fd_in, get_offset(&dummy()->\
		redir, &dummy()->redir.next)))->next = new_redir;
	else
		last_cmd->fd_in = new_redir;
}

void	new_output(char *file, int type)
{
	t_redir	*new_redir;
	t_cmd	*last_cmd;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Memory allocation error: new_redir\n");
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	last_cmd = get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, \
	&dummy()->cmd.next));
	if (last_cmd->fd_out)
		((t_redir *)get_last_node(last_cmd->fd_out, get_offset(&dummy()->\
		redir, &dummy()->redir.next)))->next = new_redir;
	else
		last_cmd->fd_out = new_redir;
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
		new_input(ft_itoa(handle_heredoc(heredoc_quote(&str[*i]), \
		get_del(str, i))), HEREDOC);
	else if (len == 2 && redir == '>')
		new_output(get_file(str, i), APPEND);
	else if (len == 1 && redir == '<')
		new_input(get_file(str, i), IN);
	else if (len == 1 && redir == '>')
		new_output(get_file(str, i), OUT);
}
