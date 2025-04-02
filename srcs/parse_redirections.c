/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:52:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/02 20:31:05 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	file_len(char *str, int i)
{
	int		len;
	int		quotes;

	len = 0;
	quotes = 0;
	while (str[i + len])
	{
		check_quotes(str[i + len], &quotes);
		if (quotes == 0 && check_metachar(str[i + len]))
			break ;
		len++;
	}
	return (len);
}

char	*get_file(char *str, int *i)
{
	int		j;
	int		len;
	char	*delimiter;

	len = file_len(str, *i);
	delimiter = malloc(sizeof(char) * len + 1);
	if (!delimiter)
		deallocate("Error> get_file");
	j = 0;
	while (j < len)
	{
		if ((str[*i] != '\'') && (str[*i] != '\"'))
		{
			delimiter[j] = str[*i];
			j++;
		}
		(*i)++;
	}
	delimiter[j] = '\0';
	return (delimiter);
}

void	new_input(char *file, int type)
{
	t_redir	*new_redir;
	t_cmd	*last_cmd;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Error> new_redir");
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
		deallocate("Error> new_redir");
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
		new_input(ft_itoa(handle_heredoc(get_file(str, i))), HEREDOC);
	else if (len == 2 && redir == '>')
		new_output(get_file(str, i), APPEND);
	else if (len == 1 && redir == '<')
		new_input(get_file(str, i), IN);
	else if (len == 1 && redir == '>')
		new_output(get_file(str, i), OUT);
}
