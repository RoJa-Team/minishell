/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:32:34 by rafasant          #+#    #+#             */
/*   Updated: 2025/01/10 17:48:54 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_ms
{
	
}				t_ms;

/*********************************************/
/*                                           */
/*                  Parsing                  */
/*                                           */
/*********************************************/

/* parse_input.c */
int		pipe_counter(char *str);
void	parse_input(char *str);
void	quote_validator(char *str);

/*********************************************/
/*                                           */
/*                 Executing                 */
/*                                           */
/*********************************************/

/**/

/*********************************************/
/*                                           */
/*          Miscellanious functions          */
/*                                           */
/*********************************************/

/* error.c */
void	deallocate(char *message);

#endif