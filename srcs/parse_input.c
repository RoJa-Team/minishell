/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/17 18:10:49 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		deallocate("Memory allocation error: init_cmd\n");
	new_cmd->arg = NULL;
	new_cmd->fd_in = NULL;
	new_cmd->fd_out = NULL;
	new_cmd->next = NULL;
	if (parse()->cmd_ll)
		((t_cmd *)get_last_node(parse()->cmd_ll, get_offset(&dummy()->cmd, \
		&dummy()->cmd.next)))->next = new_cmd;
	else
		parse()->cmd_ll = new_cmd;
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
		deallocate("Memory allocation error: new_str\n");
	j = 0;
	while (j < len && str[*i])
		new_str[j++] = str[(*i)++];
	new_str[j] = '\0';
	return (new_str);
}

void	new_arg(char *str)
{
	t_arg	*new_arg;

	if (!str)
		return ;
	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		deallocate("Memory allocation error: new_arg\n");
	new_arg->word = str;
	new_arg->next = NULL;
	if (parse()->arg_ll)
		((t_arg *)get_last_node(parse()->arg_ll, get_offset(&dummy()->arg, \
		&dummy()->arg.next)))->next = new_arg;
	else
		parse()->arg_ll = new_arg;
}

void	parse_input(char *str)
{
	int		i;

	i = 0;
	while (1)
	{
		new_cmd();
		while (str[i])
		{
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
			{
				i++;
				break ;
			}
			else if (str[i] == '<' || str[i] == '>')
				new_redir(str, &i);
			else
				new_arg(expand_str(new_str(str, &i)));
		}
		if (parse()->arg_ll)
			token_to_array();
		if (str[i] == '\0')
			break ;
	}
	cmd_to_array();
	// print_cmd();
}
