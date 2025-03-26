/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:52:54 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/26 20:59:40 by rafasant         ###   ########.fr       */
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

void	new_input(t_cmd *cmd_ll, char *file, int type)
{
	t_cmd	cmd_dummy;
	t_cmd	*last_cmd;
	t_redir	redir_dummy;
	t_redir	*new_redir;
	t_redir	*temp;

	last_cmd = get_last_node(cmd_ll, get_offset(&cmd_dummy, &cmd_dummy.next));
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Error> new_redir");
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	temp = NULL;
	if (last_cmd->fd_in)
	{
		temp = get_last_node(last_cmd->fd_in, get_offset(&redir_dummy, \
		&redir_dummy.next));
		temp->next = new_redir;
	}
	else
		last_cmd->fd_in = new_redir;
}

void	new_output(t_cmd *cmd_ll, char *file, int type)
{
	t_cmd	cmd_dummy;
	t_cmd	*last_cmd;
	t_redir	redir_dummy;
	t_redir	*new_redir;
	t_redir	*temp;

	last_cmd = get_last_node(cmd_ll, get_offset(&cmd_dummy, &cmd_dummy.next));
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		deallocate("Error> new_redir");
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	temp = NULL;
	if (last_cmd->fd_out)
	{
		temp = get_last_node(last_cmd->fd_out, get_offset(&redir_dummy, \
		&redir_dummy.next));
		temp->next = new_redir;
	}
	else
		last_cmd->fd_out = new_redir;
}

void	new_redir(t_cmd *cmd_ll, char *str, int *i)
{
	int		len;
	char	redir;

	len = 0;
	redir = str[*i];
	while (str[*i] == str[*i + len] && str[*i] != '\0')
		len++;
	*i = *i + len;
	while (str[*i] == ' ' && str[*i] != '\0')
		(*i)++;
	if (len > 2 || check_metachar(str[*i + len]) || str[*i] == '\0')
		return ((void)ft_printf("Error> Redirection Syntax error"));
	if (len == 2 && redir == '<')
		new_input(cmd_ll, ft_itoa(handle_heredoc(get_file(str, i))), HEREDOC);
	else if (len == 2 && redir == '>')
		new_output(cmd_ll, get_file(str, i), APPEND);
	else if (len == 1 && redir == '<')
		new_input(cmd_ll, get_file(str, i), IN);
	else if (len == 1 && redir == '>')
		new_output(cmd_ll, get_file(str, i), OUT);
}
