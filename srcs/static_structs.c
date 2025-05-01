/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:09:14 by rafasant          #+#    #+#             */
/*   Updated: 2025/04/25 23:29:43 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_ms	*ms(void)
{
	static t_ms	ms;

	return (&ms);
}

t_parse	*parse(void)
{
	static t_parse	parse;

	return (&parse);
}

t_dummy	*dummy(void)
{
	static t_dummy	dummy;

	return (&dummy);
}

t_catch	*catch(void)
{
	static t_catch	catch;

	return (&catch);
}
