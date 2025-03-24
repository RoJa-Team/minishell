/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/24 22:18:24 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	new_cmd(t_cmd **cmd_ll)
{
	t_cmd	dummy;
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		deallocate("Error> init_cmd");
	new_cmd->arg = NULL;
	new_cmd->fd_in = NULL;
	new_cmd->fd_out = NULL;
	new_cmd->next = NULL;
	temp = NULL;
	if (*cmd_ll)
		temp = get_last_node(*cmd_ll, get_offset(&dummy, &dummy.next));
	if (temp)
		temp->next = new_cmd;
	else
		*cmd_ll = new_cmd;
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
	if (len == 0)
		return (NULL);
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		deallocate("Error> new_str");
	j = 0;
	while (j < len)
		new_str[j++] = str[(*i)++];
	new_str[j] = '\0';
	return (new_str);
}

void	new_arg(t_parse **arg_ll, char *str)
{
	t_parse	dummy_arg;
	t_parse	*temp;
	t_parse	*new_arg;

	if (!str)
		return ;
	new_arg = malloc(sizeof(t_parse));
	if (!new_arg)
		deallocate("Error> new_arg\n");
	new_arg->token = str;
	new_arg->next = NULL;
	temp = get_last_node(*arg_ll, get_offset(&dummy_arg, &dummy_arg.next));
	if (temp)
		temp->next = new_arg;
	else
		*arg_ll = new_arg;
}

void	parse_input(t_ms *ms, char *str)
{
	int		i;
	t_cmd	*cmd_ll;
	t_parse	*arg_ll;

	i = 0;
	cmd_ll = NULL;
	while (1)
	{
		arg_ll = NULL;
		new_cmd(&cmd_ll);
		while (str[i])
		{
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
			{
				i++;
				break;
			}
			else if (str[i] == '<' || str[i] == '>')
				new_redir(cmd_ll, str, &i);	
			else
				new_arg(&arg_ll, expand_str(ms, new_str(str, &i)));
		}
		if (arg_ll)
			token_to_array(cmd_ll, arg_ll);
		if (str[i] == '\0')
			break ;
	}
	cmd_to_array(ms, cmd_ll);
	print_cmd(ms);
}
