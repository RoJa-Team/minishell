/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:42:42 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/26 00:03:11 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
		return (catch()->error_msg = "Memory allocation error: new_str\n"\
		, NULL);
	j = 0;
	while (j < len && str[*i])
		new_str[j++] = str[(*i)++];
	new_str[j] = '\0';
	return (new_str);
}

void	new_arg(char **str_arr)
{
	int		i;
	t_arg	*new_arg;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
	{
		new_arg = malloc(sizeof(t_arg));
		if (!new_arg)
			return (catch()->error_msg = "Memory allocation error: new_arg\n"\
			, (void) NULL);
		new_arg->word = str_arr[i];
		new_arg->next = NULL;
		if (parse()->arg_ll)
			((t_arg *)get_last_node(parse()->arg_ll, \
			get_offset(&dummy()->arg, &dummy()->arg.next)))->next = new_arg;
		else
			parse()->arg_ll = new_arg;
		i++;
	}
	free(str_arr);
}

void	new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (catch()->error_msg = "Memory allocation error: new_cmd\n"\
		, (void) NULL);
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

void	parse_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !ms()->here_sig && catch()->error_msg == NULL)
	{
		new_cmd();
		while (str[i] != '\0' && !ms()->here_sig && catch()->error_msg == NULL)
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
		if (parse()->arg_ll && catch()->error_msg == NULL)
			token_to_array();
	}
	if (catch()->error_msg == NULL)
		cmd_to_array();
}

void	input_check(char *input)
{
	if (verify_input(input) == 0)
	{
		parse_input(input);
		free(input);
		if (catch()->error_msg != NULL)
			deallocate(catch()->error_msg);
		if (!ms()->here_sig)
			exec_cmd();
		ms()->here_sig = 0;
		clean_cmd();
	}
	else
		free(input);
}
