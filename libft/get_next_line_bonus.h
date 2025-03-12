/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:03:13 by rafasant          #+#    #+#             */
/*   Updated: 2025/03/12 21:23:50 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
void	gnl_adjust_buffer(char *buffer, int len);
size_t	gnl_ft_strlen_c(char *str, char c);
char	*gnl_get_str(int fd, char *buffer, char *str);
char	*gnl_ft_strndup(char *str, int len);
char	*gnl_ft_strjoin_n(char *s1, char *s2, int len);

#endif